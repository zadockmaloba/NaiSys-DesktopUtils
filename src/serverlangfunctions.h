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

    static std::map<const QString, const ast_operator> functionMap()
    {
        return m_functionMap;
    }

    static void registerParameters(const QStringList &params)
    {
        params_reg = params;
    }


private://private members
    static const ast_operator println;
    static const ast_operator readfile;
    static const ast_operator writefle;
    static const ast_operator stringreplace;
    static const ast_operator stringconcat;

private://registers
    static QStringList args_reg, params_reg;
    static const std::map<const QString, const ast_operator> m_functionMap;

};

const std::map<const QString, const ast_operator> CoreFunctions::m_functionMap =
{
    {"Println", println},
    {"FileRead", readfile},
    {"FileWrite", writefle}
};

const ast_operator CoreFunctions::println = []()mutable
{
    Function func;
    func.setArguments({"fmt", "args"});
    //NOTE: Always set params after args
    func.setParameters(params_reg);
    auto fmt = func.parameters().at(0);
    StreamIO::println(QSTRING_TO_CSTR(fmt));

};

const ast_operator CoreFunctions::readfile = []()mutable
{
    Function func;
    func.setArguments({"fmt", "args"});
    //NOTE: Always set params after args
    func.setParameters(params_reg);
};

}
}

#endif // SERVERLANGFUNCTIONS_H
