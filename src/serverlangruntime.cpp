#include "serverlangruntime.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include "streamio.h"
//#include "naisyshttprequest.h"
//#include "naisyshttpresponse.h"

namespace NaiSys {
namespace ServerLang {

RunTime::RunTime()
{

}

const QRegularExpression RunTime::arrmatch = QRegularExpression("\\w+\\[\\d+\\]");
const QRegularExpression RunTime::structmatch = QRegularExpression("\\w+!\\[\\w+\\]");
const QRegularExpression RunTime::classmatch = QRegularExpression("\\w+\\-\\>\\w+");

RunTime::RunTime(const SyntaxTree &ast)
    //: m_BufferAST{ast.treeObject()}
{
    m_BufferAST.insert("runtime_symbols", QJsonObject{});
}

void RunTime::interprate(QVariantMap &ast)
{
    auto decl  = ast.value("declarations").toMap();
    auto hooks = ast.value("hooks").toMap();
    auto calls = ast.value("calls").toList();
    auto tree  = ast.value("tree").toMap();

    //decl.size() != 0 ? m_tmpParentScope = ast : m_tmpParentScope;
    if(!decl.empty()) m_tmpParentScope = ast;

    for(int i=0 ; i<decl.size() ; ++i){
        auto const _keys = decl.keys();
        qDebug() << "DECL_KEYS: " << _keys;
        auto obj = decl.value(_keys.at(i)).toMap();
        if(obj.contains("tree")){
            functionDefsHandler(obj);
            decl.find(_keys.at(i)).value() = obj;
        }
        else {
            auto rs = obj.value("init").toMap();
            if(!rs.isEmpty()){
                interprate(rs);
                //obj.find("init").value() = rs;
                obj.find("value").value() = rs.value("calls")
                        .toList().at(0)
                        .toMap().value("value");
                decl.find(_keys.at(i)).value() = obj;
                ast.find("declarations").value() = decl;
                m_tmpParentScope = ast;
            }
        }
    }
    if(ast.contains("declarations")) ast["declarations"] = decl;

    for(int i=0; i<calls.count(); ++i){
        auto obj = calls.at(i).toMap();
        functionCallsHandler(obj, ast);
        calls[i] = obj;
    }
    if(ast.contains("calls")) ast["calls"] = calls;

    for(auto &v : hooks){
        auto const obj = v.toMap();
        hooksDefsHandler(obj);
    }

    if(ast.contains("tree")) interprate(tree);

    if(ast.contains("hooks")) ast["hooks"] = hooks;
    if(ast.contains("tree")) ast["tree"] = tree;
}

const QVariantMap RunTime::CHECK_FOR_DECLARATION(const QString &vname, const QVariantMap &scope)
{
    QVariantMap ret;
    //FIXME: Create static object for this regex

    auto const decl = scope.value("declarations").toMap();
    auto const glbl_decl = m_BufferAST.value("declarations").toMap();
    auto const prnt_decl = m_tmpParentScope.value("declarations").toMap();
    auto const parms = scope.value("parameters").toList();

    if(decl.contains(vname)) ret = decl.value(vname).toMap();
    else if(prnt_decl.contains(vname)) ret = prnt_decl.value(vname).toMap();
    else if(glbl_decl.contains(vname)) ret = glbl_decl.value(vname).toMap();

    //Parse struct accessors
    else if(auto _armm = arrmatch.match(vname); _armm.hasMatch()){
        //auto arrMatch = arrmatch.match(vname);
        auto const strl = _armm.captured(0).split("[");

        auto const indx = strl.at(1).chopped(1).toInt();

        auto ob = CHECK_FOR_DECLARATION(strl.at(0), scope);
        auto arr = QJsonDocument::fromJson(ob.value("value")
                                           .toString().toUtf8()).array();
        ret.insert("value", arr.at(indx));
    }
    else if(auto _strrmm = structmatch.match(vname); _strrmm.hasMatch()){
        auto splt = vname.split("![");
        auto const _ref = splt.at(1).chopped(1);
        qDebug() << "STRUCT_ACCESSOR: " << _ref << " : " << splt.at(0);
        auto ob = CHECK_FOR_DECLARATION(splt.at(0), scope);
        auto rv = QJsonDocument::fromJson(ob.value("value")
                    .toString().toUtf8())
                    .object().toVariantMap();
        if(!rv.isEmpty()){
            QVariant fg;
            rv.contains(_ref) ? fg = rv.value(_ref) : fg = "[Undefined]";
            ret.insert("value", fg);
            ret.insert("name", splt.at(1));

            qDebug() << ret;
        }
    }
    else if(auto _clsm = classmatch.match(vname); _clsm.hasMatch()){
        auto const splt = vname.split("->");
        auto const _ref = splt.at(1);
        qDebug() << "CLASS_ACCESSOR: " << _ref << " : " << splt.at(0);
        auto ob = CHECK_FOR_DECLARATION(splt.at(0), scope);
        if(!ob.isEmpty()){
            QVariant fg;
            ob.contains(_ref) ? fg = ob.value(_ref).toMap().value("value") :
                    fg = "[Undefined]";
            ret.insert("value", fg);
            ret.insert("name", splt.at(1));

            //qDebug() << "Class_Value: " << ret.value("value");
        }
    }
    else {
        std::for_each(parms.begin(), parms.end(),
                      [vname, &ret](const QVariant &val)mutable{
            auto const tmp = val.toMap();
            if(tmp.value("name").toString() == vname){
                ret = tmp;
            }
        });
    }

    if(!ret.isEmpty()){
        auto const fg = ret.value("value");
        qDebug() << "INFERRED_TYPE: " << fg.typeName() << " : " << ret.value("name");
        if(arrmatch.match(fg.toString()).hasMatch()){
            qDebug() << "Captured array reference";
            ret = CHECK_FOR_DECLARATION(fg.toString(), scope);
        }
        else if(structmatch.match(fg.toString()).hasMatch()){
            qDebug() << "Captured array reference";
            ret = CHECK_FOR_DECLARATION(fg.toString(), scope);
        }

        ret.insert("type", fg.typeName());
        //qDebug() << "CAPTURED_DECL: " << fg;
    }

    return ret;
}

void RunTime::start()
{
    //auto ob = QJsonObject(m_BufferAST);
    interprate(m_BufferAST);
    //m_BufferAST = ob;
    //qDebug() << "[FINAL_BUFFER]: " << SyntaxTree::printTree(m_BufferAST);
    //StreamIO::println(QSTRING_TO_CSTR(SyntaxTree::printTree(m_BufferAST)));
    //if(m_hookMap.contains("index")) qDebug() << m_hookMap.value("index")();
}

void RunTime::injectRTDeclarations(const std::map<const QString, const QVariant> &rtDecls)
{
    auto old = m_BufferAST.value("declarations").toMap();
    for(auto const &[_k, _v] : rtDecls){
        old.insert(_k, QVariantMap{
                       {"name", _k},
                       {"value", _v}
                   });
    }

    m_BufferAST.find("declarations").value() = old;
    qDebug() << "INJECTED_VALUES: " << m_BufferAST.value("declarations");
}

void RunTime::functionCallsHandler(QVariantMap &fn, QVariantMap &scope)
{
    if(fn.value("type").toString() == "Core"){
        auto fname = fn.value("name").toString();

        switch (m_coreLibMap[fname]) {

        case CoreFunctions::Println:{
            auto const _args = fn.value("arguments").toList();

            auto const _str = _args.at(0).toString();
            auto const obj = CHECK_FOR_DECLARATION(_str, scope);
            QString _v;
            obj.isEmpty() ? _v=_str : _v = obj.value("value").toString();

            for(int i=1 ; i<_args.size(); ++i){
                auto rg = _args.at(i).toString();
                auto const _tmp = CHECK_FOR_DECLARATION(rg, scope);
                _tmp.isEmpty() ? rg = _args.at(i).toString() :
                                 rg = _tmp.value("value").toString();
                _v.replace("%{"+QString::number(i-1)+"}", rg);
            }

            StreamIO::println(_v.toStdString().c_str());
            //std::cout << _v.toStdString() <<std::endl;
            break;
        }

        case CoreFunctions::ReadFile:{
            auto const _args = fn.value("arguments").toList();
            //m_BufferCursor = fn.find("value");
            if(_args.size() == 2){
                //FIXME: Find a more optimized way to do this
                auto const _str_name =  _args.at(0).toString();
                auto const _fopen_type =  _args.at(1).toString();
                auto const obj = CHECK_FOR_DECLARATION(_str_name, scope);
                QString _str;
                obj.isEmpty() ? _str = _str_name : _str = obj.value("value").toString();
                _str.replace("\"", "");

                if(_fopen_type == "FILE_CHAR"){
                    QFile m_file(_str);
                    m_file.open(QIODevice::ReadOnly);
                    auto const r = m_file.readAll();
                    m_file.close();
                    fn.find("value").value() = QString(r);
                }
                else if(_fopen_type == "FILE_BIN"){
                    //TODO: Implement reading of raw bytes
                    QFile m_file(_str);
                    m_file.open(QIODevice::ReadOnly);
                    auto const r_s = m_file.bytesAvailable();
                    auto const r = m_file.read(r_s);
                    StreamIO::println("Bytes available: %arg, Bytes read: %arg",
                                      QSTRING_TO_CSTR(QString::number(r_s)),
                                      QSTRING_TO_CSTR(QString::number(r.length())));
                    m_file.close();
                    qDebug() << "READ_STRING_LEN: " << r.length();
                    fn.find("value").value() = r;
                }
                else{
                    qWarning() << "RUNTIME_ERROR: " << fname << " unknown file handle";
                }

                //fn.find("value").value() = _ret;
            }
            else UNMATCHED_PARAMETERS_ERROR(fname, 2, _args.size());
            break;
        }
        case CoreFunctions::WriteFile:{
            qDebug() << "RUNTIME_FILE_WRITE";
            auto const _args = fn.value("arguments").toList();
            if(_args.size() == 3){
                auto const _fname = _args.at(0).toString();
                auto const _dat = _args.at(1).toString();
                auto const _flag = _args.at(2).toString();
                QString _str; QByteArray _str2;
                auto const obj = CHECK_FOR_DECLARATION(_fname, scope);
                auto const obj2 = CHECK_FOR_DECLARATION(_dat, scope);

                obj.isEmpty() ? _str = _fname : _str = obj.value("value").toString();
                obj2.isEmpty() ? _str2 = _dat.toUtf8() : _str2 = obj2.value("value").toByteArray();
                _str.replace("\"", "");
                qDebug() << "WRITE_STRING_LEN: " << _str2.length()
                         << " : " << obj2.value("value").typeName();

                if(_flag == "FILE_CHAR"){
                    //qDebug() << _dat << " : "<< _str2 <<" => "<<obj2;
                    QFile m_file(_str);
                    m_file.open(QIODevice::WriteOnly);
                    auto const _b = m_file.write(_str2);
                    m_file.close();
                    fn.find("value").value() = QString::number((int)_b);
                }
                else if(_flag == "FILE_BIN"){
                    //TODO: Implement writing of raw bytes
                    //qDebug() << "WRITE_BIN_DATA: " << _str2;
                    QFile m_file(_str);
                    m_file.open(QIODevice::WriteOnly);
                    auto const _b = m_file.write(_str2);
                    m_file.close();
                    fn.find("value").value() = QString::number((int)_b);
                }
                else{
                    qWarning() << "RUNTIME_ERROR: " << fname << " unknown file handle";
                }
            }
            else UNMATCHED_PARAMETERS_ERROR(fname, 3, _args.size());
            break;
        }
        case CoreFunctions::String_Replace:{
            qDebug() << "RUNTIME_STRING_REPLACE_FN";
            auto const _args = fn.value("arguments").toList();
            if(_args.size() == 3){
                //FIXME: Find a more optimized way to do this
                auto const _str_name =  _args.at(0).toString();
                auto const _plc =  _args.at(1).toString().replace("\"","");
                auto const _repl = _args.at(2).toString().replace("\"","");
                auto const obj = CHECK_FOR_DECLARATION(_str_name, scope);
                QString _str;
                obj.isEmpty() ? _str = _str_name : _str = obj.value("value").toString();
                _str.replace(_plc, _repl);
                fn.find("value").value() = _str;
            }
            else UNMATCHED_PARAMETERS_ERROR(fname, 3, _args.size());
            break;
        }
        case CoreFunctions::String_Concat:{
            qDebug() << "RUNTIME_STRING_CONCAT_FN";
            auto const _args = fn.value("arguments").toList();
            if(_args.size() == 2){
                //FIXME: Find a more optimized way to do this
                auto const _str_name =  _args.at(0).toString().replace("\"","");
                auto const _plc =  _args.at(1).toString().replace("\"","");
                auto const obj = CHECK_FOR_DECLARATION(_str_name, scope);
                auto const obj2 = CHECK_FOR_DECLARATION(_plc, scope);
                QString _str, _str2;
                obj.isEmpty() ? _str = _str_name : _str = obj.value("value").toString();
                obj2.isEmpty() ? _str2 = _plc : _str2 = obj2.value("value").toString();
                _str.append(_str2);
                fn.find("value").value() = _str;
            }
            else UNMATCHED_PARAMETERS_ERROR(fname, 2, _args.size());
            break;
        }
        case CoreFunctions::Struct_Modify:{
            qDebug() << "RUNTIME_STRUCT_MOD_FN";
            auto const _args = fn.value("arguments").toList();
            if(_args.size() == 3){
                //FIXME: Find a more optimized way to do this
                auto const _str_name =  _args.at(0).toString();
                auto const _key = _args.at(1).toString().replace("\"","");
                auto const _plc = _args.at(2).toString().replace("\"","");
                auto const obj = CHECK_FOR_DECLARATION(_str_name, scope);
                auto const obj2 = CHECK_FOR_DECLARATION(_plc, scope);
                auto ref = QJsonDocument::fromJson(obj.value("value").toString().toUtf8()).object();
                QString _str2;
                obj2.isEmpty() ? _str2 = _plc : _str2 = obj2.value("value").toString();
                if(!ref.isEmpty()){
                    ref.find(_key).value() = _str2;
                    qDebug() << ref;
                    UPDATE_SCOPE_DECLARATIONS_VALUE(_str_name, scope, QString(QJsonDocument(ref).toJson()));
                }
                else {
                    qWarning() << "RUNTIME_ERROR: Could not read JsonObject";
                }
            }
            else UNMATCHED_PARAMETERS_ERROR(fname, 3, _args.size());
            break;
        }
        case CoreFunctions::Struct_Insert:{
            qDebug() << "RUNTIME_STRUCT_INS_FN";
            break;
        }
        case CoreFunctions::Class_Modify:{
            qDebug() << "RUNTIME_CLASS_MOD_FN";
            auto const _args = fn.value("arguments").toList();
            if(_args.size() == 2){
                //FIXME: Find a more optimized way to do this
                auto const _str_name =  _args.at(0).toString();
                //auto const _key = _args.at(1).toString().replace("\"","");
                auto const _plc = _args.at(1).toString().replace("\"","");
                auto obj = CHECK_FOR_DECLARATION(_str_name, scope);
                auto const obj2 = CHECK_FOR_DECLARATION(_plc, scope);
                //auto ref =
                QByteArray _str2;
                obj2.isEmpty() ? _str2 = _plc.toUtf8() : _str2 = obj2.value("value").toByteArray();
                if(!obj.isEmpty()){
                    obj.find("value").value() = _str2;
                    //FIXME
                    UPDATE_SCOPE_DECLARATIONS_VALUE(_str_name, m_tmpParentScope, obj);
                    UPDATE_SCOPE_DECLARATIONS_VALUE(_str_name, m_BufferAST, obj);
                }
                else {
                    qWarning() << "RUNTIME_ERROR: Could not find Class Declaration";
                }
            }
            else UNMATCHED_PARAMETERS_ERROR(fname, 2, _args.size());
            break;
        }
        case CoreFunctions::DB_Open:{
            //FIXME: Find a way to store the Database Handle in a map without copying
            // and or implictily deleting the copy constructor
            qDebug() << "RUNTIME_DATABASE_OPEN_FN";
            auto const _args = fn.value("arguments").toList();
            if(_args.size() == 1){
                auto const _dbconn = _args.at(0).toString();
                auto const obj = CHECK_FOR_DECLARATION(_dbconn, scope);
                if(!obj.isEmpty()){
                    auto const _dbparm = QJsonDocument::fromJson(obj.value("value").toString().toUtf8()).object();
                    DatabaseHandler::ConnectionStrct _strct = {
                        .db_type =     _dbparm.value("db_type").toString(),
                        .db_name =     _dbparm.value("db_name").toString(),
                        .db_host =     _dbparm.value("db_host").toString(),
                        .db_password = _dbparm.value("db_password").toString(),
                        .db_user =     _dbparm.value("db_user").toString(),
                        .db_port =     _dbparm.value("db_port").toInt()
                    };
                    //FIXME: !!!! Fix possible memory leak
                    auto _dbH = std::shared_ptr<DatabaseHandler>(new DatabaseHandler(_strct));
                    //this->m_databaseMap.insert({_dbH->dbConnectionName(), _dbH});
                    m_dbHandler = _dbH;

                    fn.find("value").value() = _dbH->dbConnectionName();
                }
                else qWarning() << "RUNTIME_ERROR: Could not find Database Handle declaration.";
            }
            else UNMATCHED_PARAMETERS_ERROR(fname, 1, _args.size());
            break;
        }
        case CoreFunctions::DB_Close:{
            qDebug() << "RUNTIME_DATABASE_CLOSE_FN";
            auto const _args = fn.value("arguments").toList();
            if(_args.size() == 1){
                auto const obj = CHECK_FOR_DECLARATION(_args.at(0).toString(), scope);
                if(!obj.isEmpty()){
                    //auto const hndl = obj.value("value").toString();
                    //auto const cls = this->m_databaseMap.find(hndl).second;
                    //auto const cls = m_dbHandler;
                    //this->m_databaseMap.remove(hndl);
                    //delete cls;
                    m_dbHandler = Q_NULLPTR;
                    qDebug() << "DATABASE: closed successfully";
                }
                else qWarning() << "RUNTIME_ERROR: Could not find Database Handle declaration.";
            }
            else UNMATCHED_PARAMETERS_ERROR(fname, 1, _args.size());
            break;
        }
        case CoreFunctions::DB_Exec:{
            qDebug() << "RUNTIME_DATABASE_EXEC_FN";
            auto const _args = fn.value("arguments").toList();
            if(_args.size() == 2){
                auto const obj = CHECK_FOR_DECLARATION(_args.at(0).toString(), scope);
                if(!obj.isEmpty()){
                    //auto const hndl = obj.value("value").toString();
                    //auto const cls = this->m_databaseMap.find(hndl).second;
                    auto const cls = m_dbHandler;
                    qDebug() << (*cls).dbConnectionName();
                    auto const _val = cls->json_runSqlQuerry(_args.at(1).toString().replace("\"", ""));
                    //auto const _val = cls->runSqlQuerry(_args.at(1).toString());
                    //qDebug() << _val;
                    fn.find("value").value() = _val;
                }
                else qWarning() << "RUNTIME_ERROR: Could not find Database Handle declaration.";
            }
            else UNMATCHED_PARAMETERS_ERROR(fname, 2, _args.size());
            break;
        }
        case CoreFunctions::DB_Write:{
            qDebug() << "RUNTIME_DATABASE_WRITE_FN";
            auto const _args = fn.value("arguments").toList();
            if(_args.size() == 4){
                auto const obj = CHECK_FOR_DECLARATION(_args.at(0).toString(), scope);
                if(!obj.isEmpty()){
                    auto const tbl_name = _args.at(1).toString().replace("\"","");
                    auto const cols_var = _args.at(2).toString();
                    auto const dat_var = _args.at(3).toString();
                    auto const cols_var_obj = CHECK_FOR_DECLARATION(cols_var, scope);
                    auto const dat_var_obj = CHECK_FOR_DECLARATION(dat_var, scope);
                    auto const cols_obj = QJsonDocument::fromJson(cols_var_obj.value("value").toString().toUtf8()).object();
                    auto const dat_obj =  QJsonDocument::fromJson(dat_var_obj.value("value").toString().toUtf8()).object();
                    auto const stat = m_dbHandler->insertJsonDataToTable(tbl_name, cols_obj, dat_obj);

                    stat ? fn.find("value").value() = "true" : fn.find("value").value() = "false";
                }
                else qWarning() << "RUNTIME_ERROR: Could not find Database Handle declaration.";
            }
            else UNMATCHED_PARAMETERS_ERROR(fname, 4, _args.size());
            break;
        }
        default:
            std::cout << "[RUNTIME_ERROR]: Unknown function: "
                      << fname.toStdString() << std::endl;
            break;
        }
    }

    else if(fn.value("type").toString() == "Local"){
        auto fname = fn.value("name").toString();
        auto ob = fn.value("tree").toMap();
        m_functionMap[fname] = [&ob, this]()
                mutable{ interprate(ob); };
        m_functionMap.value(fname)();
        fn.find("tree").value() = ob;
    }
    else if(fn.value("type").toString().startsWith("Core::If")){
        auto fname = fn.value("name").toString();
        auto ftype = fn.value("type").toString();
        auto args = fn.value("arguments").toList();
        Q_ASSERT(args.size() == 2);

        auto const obj1 = CHECK_FOR_DECLARATION(args.at(0).toString(), scope);
        auto const obj2 = CHECK_FOR_DECLARATION(args.at(1).toString(), scope);
        QString val1, val2;

        obj1.isEmpty() ? val1 = args.at(0).toString() : val1 = obj1.value("value").toString();
        obj2.isEmpty() ? val2 = args.at(1).toString() : val2 = obj2.value("value").toString();

        qDebug() << "ARG 1: " << val1;
        qDebug() << "ARG 2: " << val2;

        if(ftype.endsWith("::EQUALTO") && (val1 == val2)) m_functionMap.value(fname)();
    }

    else if(fn.value("type").toString() == "Core::Match"){
        auto args = fn.value("arguments").toList();
        auto ref = args.at(0).toString();

        auto const obj = CHECK_FOR_DECLARATION(fn.value("name").toString(), scope);
        //QJsonObject ref_obj;
        auto const obj2 = CHECK_FOR_DECLARATION(ref, scope);
        auto const tr = obj.value("tree").toMap();

        auto res = CHECK_FOR_DECLARATION(obj2.value("value").toString(), tr);

        if(res.isEmpty()){
            auto const decl = tr.value("declarations").toMap().keys();
            //qDebug() << "RUNTIME_DECLARATION_KEYS: " << decl;
            std::for_each(decl.begin(), decl.end(), [&](const QString &v)mutable{
                if(v.contains(" ... ")){
                    auto lst = v.split(" ... ");
                    int _r = obj2.value("value").toString().toInt();
                    int _a = lst.at(0).toInt();
                    int _b = lst.at(1).toInt();

                    //qDebug() << "RUNTIME_COMPARISSON: ref: " << _r << " a: " << _a << " b: " << _b;

                    if(_a <= _r && _r <= _b) res = tr.value("declarations").toMap()
                            .value(v).toMap();
                    //qDebug() << "RUNTIME_RESOLUTION: " << res;
                }
            });
        }

        //qDebug() << "MATCH RESULT: " << res;

        auto const call = res.value("tree").toMap().value("calls").toList();
        for(auto &v : call){
            auto tmp = v.toMap();
            functionCallsHandler(tmp, res);
        }
    }
}

//FIXME: This means local functions won't be able to mutate
//values out of their scope
void RunTime::functionDefsHandler(const QVariantMap &fn)
{
    auto fname = fn.value("name").toString();
    auto obj = fn;
    m_functionMap.insert(fname, [obj, this]()
                             mutable{
        auto ob = obj.value("tree").toMap();
        interprate(ob);
        obj.find("tree").value() = ob;
    });
    qDebug() << m_functionMap.keys();
}

void RunTime::variableDefsHandler(QVariantMap &var)
{

}

void RunTime::hooksDefsHandler(const QVariantMap &hook)
{
    auto fname = hook.value("name").toString();
    qDebug() << "[HOOK_NAME]: " << fname;
    auto obj = QVariantMap(hook);
    m_hookMap.insert(fname, [obj, this]()
                             mutable -> const QVariantMap{
        auto ob = obj.value("tree").toMap();
        interprate(ob);
        auto ret = CHECK_FOR_DECLARATION(obj.value("value").toString(),
                                         m_BufferAST);
        if(!ret.isEmpty()) obj.find("value").value() = ret;

        return obj.value("value").toMap();
    });
}

void RunTime::UPDATE_SCOPE_DECLARATIONS_VALUE(const QString &vname, QVariantMap &scope, const QVariant &newVal)
{
    auto decl = scope.value("declarations").toMap();
    auto itm = decl.value(vname).toMap();
    if(vname.contains("->") && !decl.isEmpty()){
        qDebug() << "MODIFY_CLASS";
        auto const splt = vname.split("->");
        auto const var = splt.at(0);
        auto inner_decl = decl.value(var).toMap();
        inner_decl.find(splt.at(1)).value() = newVal;
//        auto pdecl = inner_decl.value(splt.at(1)).toMap();
//        pdecl.find("value").value() = newVal;
//        inner_decl.find(splt.at(1)).value() = pdecl;
        decl.find(var).value() = inner_decl;
//        qDebug() << "RUNTIME_ARROW_OPR_BASE: " << var << " : " << decl;
    }
    else{
        itm.find("value").value() = newVal;
        decl.find(vname).value() = itm;
    }
    scope.find("declarations").value() = decl;
}

const QMap<QString, std::function<const QVariantMap ()> > &RunTime::hookMap() const
{return m_hookMap;}

void RunTime::setHookMap(const QMap<QString, std::function<const QVariantMap ()> > &newHookMap)
{m_hookMap = newHookMap;}

const QVariantMap &RunTime::BufferAST() const
{return m_BufferAST;}

void RunTime::setBufferAST(const QVariantMap &newBufferAST)
{m_BufferAST = newBufferAST;}

} // namespace ServerLang
} // namespace NaiSys
