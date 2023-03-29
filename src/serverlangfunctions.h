#ifndef SERVERLANGFUNCTIONS_H
#define SERVERLANGFUNCTIONS_H

#include "serverlangtypes.h"
#include "streamio.h"
#include "databasehandler.h"

#include <QProcess>
#include <QFile>

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

    static void registerParameters(const QVariantList &params)
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
    static const ast_operator dbopen;
    static const ast_operator dbexec;
    static const ast_operator dbclose;

private://registers
    static QVariantList args_reg, params_reg;
    static const std::map<const QString, const ast_operator> m_functionMap;

};

inline QVariantList CoreFunctions::args_reg = {};
inline QVariantList CoreFunctions::params_reg = {};

inline const ast_operator CoreFunctions::exec_cmd = []()mutable->value_ptr
{
    Function func;
    func.setArguments({"exec", "args"});
    //NOTE: Always set params after args
    func.setParameters(params_reg);
    auto user_args = func.parameters();
    user_args.remove(0);
    QStringList tmpList;
    std::for_each(user_args.begin(), user_args.end(),
                  [tmpList](const QVariant &v)mutable{
        tmpList << v.toString();
    });

    return std::make_shared<QVariant>(
                QProcess::execute(func.parameters().at(0).toString(), tmpList)
                );
};

inline const ast_operator CoreFunctions::println = []()mutable->value_ptr
{
    Function func;
    func.setArguments({"fmt", "args"});
    //NOTE: Always set params after args
    func.setParameters(params_reg);
    auto fmt = func.parameters().at(0).toString();

    auto user_args = func.parameters();
    user_args.remove(0);

    QStringList tmpList;
    std::for_each(user_args.begin(), user_args.end(),
                  [tmpList](const QVariant &v)mutable{
        tmpList << v.toString();
    });

    for(int i=0; i<user_args.size(); ++i) {
        fmt.replace("%{"+QString::number(i)+"}", tmpList.at(i));
    }

    return std::make_shared<QVariant>(
                (int)StreamIO::println(QSTRING_TO_CSTR(fmt))
                );

};

inline const ast_operator CoreFunctions::readfile = []()mutable->value_ptr
{
    Function func;
    func.setArguments({"file", "args"});
    //NOTE: Always set params after args
    func.setParameters(params_reg);
    if(!(params_reg.size() == 1)) {
        //throw "[Core::FileRead]: Invalid number of args; expected 1.";
        return {};
    }
    QFile m_file(params_reg.at(0).toString());
    m_file.open(QIODevice::ReadOnly);
    auto const ret = m_file.read(m_file.bytesAvailable());
    m_file.close();
    return std::make_shared<QVariant>(ret);
};

inline const ast_operator CoreFunctions::writefile = []()mutable->value_ptr
{
    Function func;
    func.setArguments({"file", "args"});
    //NOTE: Always set params after args
    func.setParameters(params_reg);
    if(!(params_reg.size() == 2)) {
        //throw "[Core::FileWrite]: Invalid number of args; expected 2.";
        return {};
    }
    QFile m_file(params_reg.at(0).toString());
    m_file.open(QIODevice::WriteOnly);
    auto const ret = m_file.write(params_reg.at(1).toByteArray());
    m_file.close();
    return std::make_shared<QVariant>(ret);
};

inline const ast_operator CoreFunctions::dbopen = []()mutable->value_ptr
{
    Function func;
    func.setArguments({"file", "args"});
    //NOTE: Always set params after args
    func.setParameters(params_reg);
    if(!(params_reg.size() == 1)) {
        //throw "[Core::Db::Open]: Invalid number of args; expected 1.";
        return {};
    }
    auto const ret = QVariant::fromValue(
                new DatabaseHandler(params_reg.at(0).toJsonObject())
                );
    return std::make_shared<QVariant>(ret);
};

inline const ast_operator CoreFunctions::dbexec = []()mutable->value_ptr
{
    Function func;
    func.setArguments({"file", "args"});
    //NOTE: Always set params after args
    func.setParameters(params_reg);
    if(!(params_reg.size() >= 2)) {
        //throw "[Core::Db::Open]: Invalid number of args; expected 2.";
        return {};
    }

    auto dbHandle = func.parameters().at(0).value<DatabaseHandler *>();
    if(dbHandle == nullptr) {
        qWarning() << "[SERVERLANG]: Calling uninitialized reference [DB]";
        return {};
    }

    auto fmt = func.parameters().at(1).toString();

    auto user_args = func.parameters();
    user_args.remove(0, 2);

    QStringList tmpList;
    std::for_each(user_args.begin(), user_args.end(),
                  [tmpList](const QVariant &v)mutable{
        tmpList << v.toString();
    });

    for(int i=0; i<user_args.size(); ++i) {
        fmt.replace("%{"+QString::number(i)+"}", tmpList.at(i));
    }

    auto ret = dbHandle->json_runSqlQuerry(fmt);

    return std::make_shared<QVariant>(ret);
};

inline const ast_operator CoreFunctions::dbclose = []()mutable->value_ptr
{
    Function func;
    func.setArguments({"file", "args"});
    //NOTE: Always set params after args
    func.setParameters(params_reg);
    if(!(params_reg.size() == 1)) {
        //throw "[Core::Db::Open]: Invalid number of args; expected 1.";
        return {};
    }

    auto dbHandle = func.parameters().at(0).value<DatabaseHandler *>();
    if(dbHandle == nullptr) {
        qWarning() << "[SERVERLANG]: Calling uninitialized reference [DB]";
        return {};
    }

    qDebug() << "[SERVERLANG]: Freeing DB object: " << dbHandle;

    delete dbHandle;

    return std::make_shared<QVariant>(true);
};

inline const std::map<const QString, const ast_operator> CoreFunctions::m_functionMap =
{
    {"Core::Exec"     , exec_cmd},
    {"Core::Println"  , println},
    {"Core::FileRead" , readfile},
    {"Core::FileWrite", writefile},
    {"Core::Db::Open" , dbopen},
    {"Core::Db::Exec"  , dbexec},
    {"Core::Db::Close", dbclose}
};

}
}

#endif // SERVERLANGFUNCTIONS_H
