#ifndef SERVERLANGFUNCTIONS_H
#define SERVERLANGFUNCTIONS_H

#include "serverlangtypes.h"
#include "streamio.h"
#include "databasehandler.h"

#include <QProcess>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

namespace NaiSys {
namespace ServerLang {

class CoreFunctions
{
public:
    CoreFunctions() = default;

    static std::map<const QString, const ast_operator> &functionMap() { return m_functionMap; }

    static void registerParameters(const QVariantMap &params)
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
    static const ast_operator mkjson;
    static const ast_operator jsnstringify;

private://registers
    static QVariantMap args_reg, params_reg;
    static std::map<const QString, const ast_operator> m_functionMap;
};

inline QVariantMap CoreFunctions::args_reg = {};
inline QVariantMap CoreFunctions::params_reg = {};

inline const ast_operator CoreFunctions::exec_cmd = []() mutable -> value_raw_ptr {
    Function func;
    func.setArguments({"exec", "args"});
    //NOTE: Always set params after args
    func.setParameters(params_reg);
    auto user_args = func.parameters()
            .value("[...]", QVariantMap{}).toMap();
    QStringList tmpList;
    std::for_each(user_args.begin(), user_args.end(),
                  [tmpList](const QVariant &v)mutable{
        tmpList << v.toString();
    });

    return new QVariant(
        QProcess::execute(func.parameters().value("fmt", QString{""}).toString(), tmpList));
};

inline const ast_operator CoreFunctions::println = []() mutable -> value_raw_ptr {
    Function func;
    func.setArguments({"fmt", "args"});
    //NOTE: Always set params after args
    func.setParameters(params_reg);
    auto fmt = func.parameters().value("fmt", QString{""}).toString();

    auto user_args = func.parameters()
            .value("[...]", QVariantMap{}).toMap();
    QStringList tmpList = {};

    for(auto const &v : user_args) {
        tmpList << v.toString();
    }

    for(int i=0; i<tmpList.size(); ++i) {
        fmt.replace("%{"+QString::number(i)+"}", tmpList.at(i));
    }

    return new QVariant((int) StreamIO::println(QSTRING_TO_CSTR(fmt)));
};

inline const ast_operator CoreFunctions::readfile = []() mutable -> value_raw_ptr {
    Function func;
    func.setArguments({"file"});
    //NOTE: Always set params after args
    func.setParameters(params_reg);
    if(!(params_reg.size() == 1)) {
        //throw "[Core::FileRead]: Invalid number of args; expected 1.";
        return {};
    }
    QFile m_file(params_reg.value("file", QString{""}).toString());
    m_file.open(QIODevice::ReadOnly);
    auto const ret = m_file.read(m_file.bytesAvailable());
    m_file.close();
    return new QVariant(ret);
};

inline const ast_operator CoreFunctions::writefile = []() mutable -> value_raw_ptr {
    Function func;
    func.setArguments({"file", "data"});
    //NOTE: Always set params after args
    func.setParameters(params_reg);
    if(!(params_reg.size() == 2)) {
        //throw "[Core::FileWrite]: Invalid number of args; expected 2.";
        return {};
    }
    QFile m_file(params_reg.value("file", QString{""}).toString());
    m_file.open(QIODevice::WriteOnly);
    auto const ret = m_file.write(params_reg
                                  .value("data", QByteArray{""})
                                  .toByteArray());
    m_file.close();
    return new QVariant(ret);
};

inline const ast_operator CoreFunctions::dbopen = []() mutable -> value_raw_ptr {
    Function func;
    func.setArguments({"settigs"});
    //NOTE: Always set params after args
    func.setParameters(params_reg);
    if(!(params_reg.size() == 1)) {
        //throw "[Core::Db::Open]: Invalid number of args; expected 1.";
        return {};
    }
    auto const ret = QVariant::fromValue(
                new DatabaseHandler(params_reg
                                    .value("settings", QJsonObject{})
                                    .toJsonObject())
                );
    return new QVariant(ret);
};

inline const ast_operator CoreFunctions::dbexec = []() mutable -> value_raw_ptr {
    Function func;
    func.setArguments({"handle", "fmt", "args"});
    //NOTE: Always set params after args
    func.setParameters(params_reg);
    if(!(params_reg.size() >= 2)) {
        //throw "[Core::Db::Open]: Invalid number of args; expected 2.";
        return {};
    }

    auto dbHandle = func.parameters().value("handle").value<DatabaseHandler *>();
    if(dbHandle == nullptr) {
        qWarning() << "[SERVERLANG]: Calling uninitialized reference [DB]";
        return {};
    }

    auto fmt = func.parameters().value("fmt", QString{}).toString();

    auto user_args = func.parameters()
            .value("[...]", QVariantMap{}).toMap();
    QStringList tmpList;

    for(auto const &v : user_args) {
        tmpList << v.toString();
    }

    for(int i=0; i<user_args.size(); ++i) {
        fmt.replace("%{"+QString::number(i)+"}", tmpList.at(i));
    }

    auto ret = dbHandle->json_runSqlQuerry(fmt);

    return new QVariant(ret);
};

inline const ast_operator CoreFunctions::dbclose = []() mutable -> value_raw_ptr {
    Function func;
    func.setArguments({"handle"});
    //NOTE: Always set params after args
    func.setParameters(params_reg);
    if(!(params_reg.size() == 1)) {
        //throw "[Core::Db::Open]: Invalid number of args; expected 1.";
        return {};
    }

    auto dbHandle = func.parameters().value("handle").value<DatabaseHandler *>();
    if(dbHandle == nullptr) {
        qWarning() << "[SERVERLANG]: Calling uninitialized reference [DB]";
        return {};
    }

    qDebug() << "[SERVERLANG]: Freeing DB object: " << dbHandle;

    delete dbHandle;

    return new QVariant(true);
};

inline const ast_operator CoreFunctions::mkjson = []() mutable -> value_raw_ptr {
    Function func;
    func.setArguments({"fmt"});
    //NOTE: Always set params after args
    func.setParameters(params_reg);
    if(!(params_reg.size() == 1)) {
        return {};
    }

    auto obj = QJsonDocument::fromJson(
                func.parameters().value("fmt", QByteArray{}).toByteArray()
                ).object();

    return new QVariant(obj);
};

inline const ast_operator CoreFunctions::jsnstringify = []() mutable -> value_raw_ptr {
    Function func;
    func.setArguments({"object"});
    //NOTE: Always set params after args
    func.setParameters(params_reg);
    if(!(params_reg.size() == 1)) {
        return {};
    }

    auto obj = func.parameters().value("object", QJsonObject{}).toJsonObject();
    auto string = QJsonDocument(obj).toJson();

    return new QVariant(string);
};

inline std::map<const QString, const ast_operator> CoreFunctions::m_functionMap
    = {{"Core::Exec", exec_cmd},
       {"Core::Println", println},
       {"Core::FileRead", readfile},
       {"Core::FileWrite", writefile},
       {"Core::Db::Open", dbopen},
       {"Core::Db::Exec", dbexec},
       {"Core::Db::Close", dbclose},
       {"Core::Json::Make", mkjson},
       {"Core::Json::Stringify", jsnstringify}};
} // namespace ServerLang
}

#endif // SERVERLANGFUNCTIONS_H
