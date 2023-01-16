#ifndef NAISYS_SERVERLANG_RUNTIME_H
#define NAISYS_SERVERLANG_RUNTIME_H

#include <QObject>
#include <QJsonObject>
#include <QStringList>

#include <QMap>
#include <QRegularExpression>

#include <algorithm>
#include <functional>
#include <map>

#include "serverlangsyntaxtree.h"
#include "databasehandler.h"
#include "databasepool.h"

namespace NaiSys {
namespace ServerLang {

class RunTime
{
    enum class CoreFunctions{
        Println = 1,
        ReadFile,
        WriteFile,
        String_Replace,
        String_Concat,
        Struct_Modify,
        Struct_Insert,
        Class_Modify,
        DB_Open,
        DB_Close,
        DB_Exec,
        DB_Write
    };
    const QMap<QString, CoreFunctions> m_coreLibMap = {
        {"Println",       CoreFunctions::Println},
        {"FileRead",      CoreFunctions::ReadFile},
        {"FileWrite",     CoreFunctions::WriteFile},
        {"StringReplace", CoreFunctions::String_Replace},
        {"StringConcat",  CoreFunctions::String_Concat},
        {"StructModify",  CoreFunctions::Struct_Modify},
        {"StructInsert",  CoreFunctions::Struct_Insert},
        {"ClassModify",   CoreFunctions::Class_Modify},
        {"DatabaseOpen",  CoreFunctions::DB_Open},
        {"DatabaseClose", CoreFunctions::DB_Close},
        {"DatabaseExec",  CoreFunctions::DB_Exec},
        {"DatabaseWrite", CoreFunctions::DB_Write}
    };
public:
    RunTime();
    explicit RunTime(const SyntaxTree &ast);
    inline const QVariantMap CHECK_FOR_DECLARATION(const QString &vname, const QVariantMap &scope);
    void start();
    void injectRTDeclarations(const std::map<const QString, const QVariant> &rtDecls);

    const QVariantMap &BufferAST() const;
    void setBufferAST(const QVariantMap &newBufferAST);

    const QMap<QString, std::function<const QVariantMap ()> > &hookMap() const;
    void setHookMap(const QMap<QString, std::function<const QVariantMap ()> > &newHookMap);

private:
    void interprate(QVariantMap &ast);
    void functionCallsHandler(QVariantMap &fn, QVariantMap &scope);
    void functionDefsHandler(const QVariantMap &fn);
    void variableDefsHandler(QVariantMap &var);
    void hooksDefsHandler(const QVariantMap &hook);

private: //helpers
    void UPDATE_SCOPE_DECLARATIONS_VALUE(const QString &vname, QVariantMap &scope, const QVariant &newVal);
    inline void UNMATCHED_PARAMETERS_ERROR(const QString &fname, int reqArgs, int argSize){
        switch ((int)(argSize < reqArgs)) {
        case true:{
            qDebug() << "RUNTIME_ERROR: " << fname << " has less arguments";
            break;
        }
        case false:{
            qDebug() << "RUNTIME_ERROR: " << fname << " has excess arguments";
            break;
        }
        default:
            break;
        }
    }

private:
     QMap<QString, std::function<void()>> m_functionMap;
     QMap<QString, std::function<const QVariantMap ()>> m_hookMap;
     //std::map<QString, std::shared_ptr<DatabaseHandler>> m_databaseMap;
     DatabasePool m_databaseMap;
     QVariantMap m_BufferAST, m_tmpParentScope;
     QVariantMap::Iterator m_BufferCursor;
     std::shared_ptr<DatabaseHandler> m_dbHandler;

private:
    static const QRegularExpression arrmatch;
    static const QRegularExpression structmatch;
    static const QRegularExpression classmatch;

};

} // namespace ServerLang
} // namespace NaiSys

#endif // NAISYS_SERVERLANG_RUNTIME_H
