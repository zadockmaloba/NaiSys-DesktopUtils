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

#include "databasehandler.h"
#include "databasepool.h"
#include "serverlangnode.h"

namespace NaiSys {
namespace ServerLang {

class RunTime
{

public:
    RunTime();
    explicit RunTime(const STNode::nodeptr &ast);
    inline const QVariantMap CHECK_FOR_DECLARATION(const QString &vname, const QVariantMap &scope);
    void start();
    void injectRTDeclarations(const std::vector<STNode::nodeptr> &rtDecls);

    const STNode::nodeptr &BufferAST() const;
    void setBufferAST(const STNode::nodeptr &newBufferAST);

    const QMap<QString, std::function<const QVariantMap ()> > &hookMap() const;
    void setHookMap(const QMap<QString, std::function<const QVariantMap ()> > &newHookMap);

    void interprate(const STNode::nodeptr &ast);

private:
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
    inline const value_ptr get_rhs_value(const STNode::nodeptr &rhs) {
        value_ptr ret = {};
        for(auto &_v : rhs->declarationMap()) {
            if(_v->second()->type() == NodeType::VARIABLE_EXPRESSION) {
                try {
                    auto const _var = _v->second();
                    auto ptr = _var->check_for_declaration(_var->value()->toString());
                    auto const refval = ptr->value();
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
                    interprate(rhs);
                    //qDebug() << "Value after call: " << _v->second()->value();
                }
                catch(...) {
                    qWarning() << "WARNING: Cannot execute nested function";
                }
            }
            else if(_v->second()->type() == NodeType::STRUCT_ACCESSOR) {
                try {
                    auto const _strct = _v->second();
                    auto const _key = _strct->declarationMap()[0]
                            .second()->value()
                            ->toString();
                    auto ptr = _strct->check_for_declaration(_strct->value()->toString());
                    auto const _dict = ptr->value()->toJsonObject();
                    auto const _key_val = _dict.contains(_key) ?
                                _dict.find(_key).value() :
                                QJsonValue{"__NULL__"};

                    _v->second()->setValue(std::make_shared<QVariant>(_key_val));
                }
                catch(...) {
                    qWarning() << "WARNING: Cannot find struct field";
                }
            }
            ret = _v->second()->value();
        }
        return ret;
    }

private:
     QMap<QString, std::function<void()>> m_functionMap;
     QMap<QString, std::function<const QVariantMap ()>> m_hookMap;
     //std::map<QString, std::shared_ptr<DatabaseHandler>> m_databaseMap;
     DatabasePool m_databaseMap;
     STNode::nodeptr m_BufferAST, m_tmpParentScope;
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
