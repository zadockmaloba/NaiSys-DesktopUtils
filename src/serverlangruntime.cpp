#include "serverlangruntime.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>

#include "serverlangcore.h"
//#include "libpython.h"

namespace NaiSys {
namespace ServerLang {

RunTime::RunTime()
{

}

RunTime::RunTime(const STNode::nodeptr &ast)
    : m_BufferAST{ast}
{
    //m_BufferAST.insert("runtime_symbols", QJsonObject{});
}

void RunTime::interprate(const STNode::nodeptr &ast)
{
    auto decls  = ast->declarationMap();
    for( auto &v : decls ) {
        auto temp = v;
        switch (temp->second()->type()) {
        case NodeType::CALL_EXPRESSION:{
            auto nm = temp->second()->name();
            qDebug() << "Executing Function symbol: " << nm;
            if (nm.toString().contains("://"))
                nm = nm.toString().split("://").at(1);

            QVariantMap _plist;
            for(auto &_v : temp->second()->declarationMap()) {
                if(_v->second()->type() == NodeType::VARIABLE_EXPRESSION) {
                    try {
                        auto const _var = _v->second();
                        auto ptr = _var->check_for_declaration(_var->referencedId());
                        auto refval = ptr->value();
                        _v->second()->setValue(refval);
                        //qDebug() << "Referenced value: " << _v->second()->value();
                    }
                    catch(...) {
                        qWarning() << "Unable to get reference value";
                    }
                }
                else if(_v->second()->type() == NodeType::CALL_EXPRESSION) {
                    try {
                        //qDebug() << "Value before call: " << _v->second()->value();
                        interprate(temp->second());
                        //qDebug() << "Value after call: " << _v->second()->value();
                    }
                    catch(...) {
                        qWarning() << "WARNING: Cannot execute nested function";
                    }
                }
                else if(_v->second()->type() == NodeType::PARAMETER_LABEL) {
                    try {
                        //qDebug() << "Value before call: " << _v->second()->value();
                        interprate(temp->second());
                        //qDebug() << "Value after call: " << _v->second()->value();
                    }
                    catch(...) {
                        qWarning() << "WARNING: Cannot interprate parameter label";
                    }
                }
                else if(_v->second()->type() == NodeType::VARIADIC_PARAMETER_LABEL) {
                    try {
                        //qDebug() << "Value before call: " << _v->second()->value();
                        interprate(_v->second());
                        QVariantMap _l;
                        int tmp_indx = 0;
                        for(auto &_t : _v->second()->declarationMap()) {
                            _l.insert(QString::number(tmp_indx), *_t->second()->value());
                            tmp_indx += 1;
                        }
                        auto const _var = new QVariant(_l);
                        _v->second()->setValue(_var);
                        //qDebug() << "Value after call: " << _v->second()->value();
                    }
                    catch(...) {
                        qWarning() << "WARNING: Cannot interprate parameter label";
                    }
                }
                _plist.insert(_v->second()->name().toString(), *_v->second()->value());
            }
            //TODO: Make parameters map a variant list
            temp->second()->setParametersMap(_plist);
            if (temp->second()->name().toString().contains("://Core::")) {
                try {
                    temp->second()->setValue(Core::exec(nm, temp->second()->parametersMap()));
                }
                catch(...) {
                    qWarning() << "[WARNING]: Calling undefined function: " << temp->second()->name();
                }
            } else {
                try {
                    auto const scp = Core::exec(nm, {})->value<STNode::nodeptr>();
                    interprate(scp);
                    temp->second()->setValue( scp->value() );
                }
                catch(...){
                    qWarning() << "[WARNING]: Calling undefined function: " << temp->second()->name();
                }
            }
            break;
        }

        case NodeType::VARIANT: {
            auto const _val = get_rhs_value(temp->second());
            temp->second()->setValue(_val);
            break;
        }

        case NodeType::VARIABLE_EXPRESSION: {
            auto const _val = get_rhs_value(temp->second());
            if( !(_val == nullptr) ) {
                auto refptr = temp->second()
                            ->check_for_declaration(temp->second()->referencedId());
                refptr->setValue(_val);
            } else {
                auto refptr = temp->second()
                            ->check_for_declaration(temp->second()->referencedId());
                temp->second()->setValue(refptr->value());
            }
            //qDebug() << "EXPRESSION VALUE: " << refptr->value();
            break;
        }

        case NodeType::FUNCTION: {
            qDebug() << "Declaring function: " << temp->second()->name();
            Core::define(temp->second());
            break;
        }

        case NodeType::PY_SCOPE:
            //LibPython::execute_string(temp->second()->value()->toString().toStdString().c_str());
            fprintf(stderr, "[WARNING]: Python scopes are depricated");
            break;

        case NodeType::RETURN_EXPRESSION: {
            auto const _val = get_rhs_value(temp->second());

            qDebug() << "[RETURN_EXP_PARENT]: " << temp->second()->parentScope()->name();
            temp->second()->parentScope()->setValue(_val);
            break;
        }

        case NodeType::STRUCT_ACCESSOR: {
            auto const _val = get_rhs_value(temp->second());
            break;
        }

        case NodeType::PARAMETER_LABEL: {
            auto const _val = get_rhs_value(temp->second());
            temp->second()->setValue(_val);
            break;
        }

        default:
            break;
        }
    }
}

const QVariantMap RunTime::CHECK_FOR_DECLARATION(const QString &vname, const QVariantMap &scope)
{
    QVariantMap ret;

    return ret;
}

void RunTime::start()
{
    interprate(m_BufferAST);
}

void RunTime::injectRTDeclarations(const std::vector<STNode::nodeptr> &rtDecls)
{
    for(auto &v: rtDecls) {
        v->setParentScope(m_BufferAST);
        m_BufferAST->add_declaration(std::move(v));
    }
}

void RunTime::functionCallsHandler(QVariantMap &fn, QVariantMap &scope)
{

}

//FIXME: This means local functions won't be able to mutate
//values out of their scope
void RunTime::functionDefsHandler(const QVariantMap &fn)
{

}

void RunTime::variableDefsHandler(QVariantMap &var)
{

}

void RunTime::hooksDefsHandler(const QVariantMap &hook)
{

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

const QMap<const QString, std::function<const QVariantMap()> > &RunTime::hookMap() const
{return m_hookMap;}

void RunTime::setHookMap(const QMap<const QString, std::function<const QVariantMap()> > &newHookMap)
{m_hookMap = newHookMap;}

const STNode::nodeptr &RunTime::BufferAST() const
{return m_BufferAST;}

void RunTime::setBufferAST(const STNode::nodeptr &newBufferAST)
{m_BufferAST = newBufferAST;}

} // namespace ServerLang
} // namespace NaiSys
