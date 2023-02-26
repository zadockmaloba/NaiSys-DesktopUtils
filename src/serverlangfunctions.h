#ifndef SERVERLANGFUNCTIONS_H
#define SERVERLANGFUNCTIONS_H

#include "serverlangtypes.h"
#include "streamio.h"

#include <QProcess>

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
    static const ast_operator exec_cmd;
    static const ast_operator println;
    static const ast_operator readfile;
    static const ast_operator writefile;
    static const ast_operator stringreplace;
    static const ast_operator stringconcat;

private://registers
    static QStringList args_reg, params_reg;
    static const std::map<const QString, const ast_operator> m_functionMap;

};

inline QStringList CoreFunctions::args_reg = {};
inline QStringList CoreFunctions::params_reg = {};

inline const ast_operator CoreFunctions::exec_cmd = []()mutable
{
    Function func;
    func.setArguments({"exec", "args"});
    //NOTE: Always set params after args
    func.setParameters(params_reg);
    auto user_args = func.parameters();
    user_args.remove(0);

    QProcess::execute(func.parameters().at(0), user_args);
};

inline const ast_operator CoreFunctions::println = []()mutable
{
    Function func;
    func.setArguments({"fmt", "args"});
    //NOTE: Always set params after args
    func.setParameters(params_reg);
    auto fmt = func.parameters().at(0);

    auto user_args = func.parameters();
    user_args.remove(0);

    for(int i=0; i<user_args.size(); ++i) {
        fmt.replace("%{"+QString::number(i)+"}", user_args.at(i));
    }

    StreamIO::println(QSTRING_TO_CSTR(fmt));

};

inline const ast_operator CoreFunctions::readfile = []()mutable
{
    Function func;
    func.setArguments({"file", "args"});
    //NOTE: Always set params after args
    func.setParameters(params_reg);
};

inline const ast_operator CoreFunctions::writefile = []()mutable
{

};

inline const std::map<const QString, const ast_operator> CoreFunctions::m_functionMap =
{
    {"Exec"     , exec_cmd},
    {"Println"  , println},
    {"FileRead" , readfile},
    {"FileWrite", writefile}
};

}
}

#endif // SERVERLANGFUNCTIONS_H
