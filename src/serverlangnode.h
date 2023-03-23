#ifndef NAISYS_SERVERLANG_STNODE_H
#define NAISYS_SERVERLANG_STNODE_H

#include <QString>
#include <QVariant>
#include <QByteArray>
#include <QMap>
#include <QSharedPointer>
#include <map>

#include "naisysindexedmap.h"

namespace NaiSys {
namespace ServerLang {

enum class NodeType {
    ARRAY = 2,
    BOOL,
    INTEGER,
    DOUBLE,
    FLOAT,
    BYTEARRAY,
    STRING,
    LITERAL,
    VARIANT,
    STRUCT,
    CLASS,
    HOOK,
    FUNCTION,
    SCOPE,
    PY_SCOPE,
    IF_STATEMENT,
    MATCH_STATEMENT,
    BINARY_EXPRESSION,
    RETURN_EXPRESSION,
    CALL_EXPRESSION,
    VARIABLE_EXPRESSION
};

using ast_operator = std::function<QVariant ()>;
using operatorscope = QMap<const QString, ast_operator>;


class STNode
{
public://Typedefs
    using nodeptr = std::shared_ptr<STNode>;
    using declscope = NaiSys::Core::IndexedMap<const QString, nodeptr>;

public:
    STNode() = default;
    ~STNode(){}

public: // helper methods
    const nodeptr check_for_declaration(const QString &name);
    void add_declaration(const nodeptr &decl);
    static NodeType get_typecode_from_typename(const QString &tname);

public: //GETTERS AND SETTERS
    QString name() const;
    void setName(const QString &newName);

    nodeptr parentScope() const;
    void setParentScope(const nodeptr &newParentScope);

    QVariant value() const;
    void setValue(const QVariant &newValue);

    nodeptr innerScope() const;
    void setInnerScope(const nodeptr &newInnerScope);

    operatorscope operatorMap() const;
    void setOperatorMap(const operatorscope &newOperatorMap);

    NodeType type() const;
    void setType(NodeType newType);

    operatorscope methodMap() const;
    void setMethodMap(operatorscope newMethodMap);

    nodeptr operand() const;
    void setOperand(const nodeptr &newOperand);

    QVariant returnval() const;
    void setReturnval(const QVariant &newReturnval);

    QByteArray raw() const;
    void setRaw(const QByteArray &newRaw);

    declscope declarationMap() const;
    void setDeclarationMap(const declscope newDeclarationMap);

    QString typeName() const;
    void setTypeName(const QString &newTypeName);

    QVariantList parametersMap() const;
    void setParametersMap(const QVariantList &newParametersMap);

protected:
    declscope m_declarationMap;
    operatorscope m_operatorMap, m_methodMap;
    nodeptr m_operand,
    m_parentScope,
    m_innerScope;

private: //Private members
    QVariantList m_parametersMap;
    QByteArray m_raw;
    QString m_name, m_typeName;
    QVariant m_value = QByteArray(),
    m_returnval = QByteArray();
    NodeType m_type;
};

} // namespace ServerLang
} // namespace NaiSys

#endif // NAISYS_SERVERLANG_STNODE_H
