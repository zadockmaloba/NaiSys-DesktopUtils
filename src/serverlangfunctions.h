#ifndef SERVERLANGFUNCTIONS_H
#define SERVERLANGFUNCTIONS_H

#include "serverlangtypes.h"
#include "streamio.h"

namespace NaiSys {
namespace ServerLang {

class CoreFunctions
{
public:
    CoreFunctions() = default;

    std::map<const QString, const ast_operator> functionMap() const
    {
        return m_functionMap;
    }

private://registers
    QStringList args_reg, params_reg;
    const std::map<const QString, const ast_operator> m_functionMap =
    {
        {"Println", println},
        {"FileRead", readfile},
        {"FileWrite", writefle}
    };

private://private members
    const ast_operator println = [this]()mutable
    {
        Function func;
        func.setArguments({"fmt", "args"});
        //NOTE: Always set params after args
        func.setParameters(params_reg);
        auto fmt = func.parameters().at(0);
        StreamIO::println(QSTRING_TO_CSTR(fmt));

    };
    const ast_operator readfile = [this]()mutable
    {
        Function func;
        func.setArguments({"fmt", "args"});
        //NOTE: Always set params after args
        func.setParameters(params_reg);
    };
    const ast_operator writefle;
    const ast_operator stringreplace;
    const ast_operator stringconcat;

};

}
}

#endif // SERVERLANGFUNCTIONS_H
