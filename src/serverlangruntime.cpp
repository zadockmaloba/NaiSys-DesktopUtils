#include "serverlangruntime.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>

#include "streamio.h"
#include "serverlangcore.h"
#include "libpython.h"
//#include "naisyshttprequest.h"
//#include "naisyshttpresponse.h"

namespace NaiSys {
namespace ServerLang {

RunTime::RunTime()
{

}

RunTime::RunTime(const SyntaxTree &ast)
    : m_BufferAST{ast}
{
    //m_BufferAST.insert("runtime_symbols", QJsonObject{});
}

void RunTime::interprate(STNode &ast)
{
    auto decls  = std::move(ast.declarationMap());
    for( auto &v : decls ) {
        auto temp = v;
        switch (temp->type()) {
        case NodeType::CALL_EXPRESSION:{
            auto nm = temp->name();
            qDebug() << "Executing Function symbol: " << nm;
            if(nm.contains("://")) nm = nm.split("://").at(1);
            Core::exec(nm, temp->parametersMap());
            break;
        }
        case NodeType::FUNCTION:
            qDebug() << "Declaring function: " << temp->name();
            Core::define(temp->name(), temp->parametersMap());
            break;

        case NodeType::PY_SCOPE:
            LibPython::execute_string(temp->value().toString().toStdString().c_str());
            break;
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

void RunTime::injectRTDeclarations(const std::map<const QString, const QVariant> &rtDecls)
{

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

const QMap<QString, std::function<const QVariantMap ()> > &RunTime::hookMap() const
{return m_hookMap;}

void RunTime::setHookMap(const QMap<QString, std::function<const QVariantMap ()> > &newHookMap)
{m_hookMap = newHookMap;}

const STNode &RunTime::BufferAST() const
{return m_BufferAST;}

void RunTime::setBufferAST(const STNode &newBufferAST)
{m_BufferAST = newBufferAST;}

} // namespace ServerLang
} // namespace NaiSys
