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
#include "serverlangnode.h"
#include "serverlangfunctions.h"

namespace NaiSys {
namespace ServerLang {

class RunTime
{

public:
    RunTime();
    explicit RunTime(const SyntaxTree &ast);
    inline const QVariantMap CHECK_FOR_DECLARATION(const QString &vname, const QVariantMap &scope);
    void start();
    void injectRTDeclarations(const std::map<const QString, const QVariant> &rtDecls);

    const STNode &BufferAST() const;
    void setBufferAST(const STNode &newBufferAST);

    const QMap<QString, std::function<const QVariantMap ()> > &hookMap() const;
    void setHookMap(const QMap<QString, std::function<const QVariantMap ()> > &newHookMap);

private:
    void interprate(STNode &ast);
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
     STNode m_BufferAST, m_tmpParentScope;
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
