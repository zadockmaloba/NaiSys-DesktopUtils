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
    VARIABLE_EXPRESSION,
    STRUCT_ACCESSOR,
    PARAMETER_LABEL,
    VARIADIC_PARAMETER_LABEL
};

using value_ptr = std::unique_ptr<QVariant>;
using value_raw_ptr = QVariant *;
using ast_operator = std::function<value_raw_ptr()>;
using operatorscope = QMap<const QString, ast_operator>;


class STNode
{
public://Typedefs
    using nodeptr = std::shared_ptr<STNode>;
    using declscope = NaiSys::Core::IndexedMap<QStringView, nodeptr>;

public:
    STNode() = default;
    ~STNode()
    {
        //delete m_value;
        //delete m_returnval;
    }

public: // helper methods
    const nodeptr check_for_declaration(QStringView name);
    void add_declaration(const nodeptr &decl);
    static NodeType get_typecode_from_typename(QStringView tname);

public: //GETTERS AND SETTERS
    QStringView name() const;
    void setName(const QString &newName);

    nodeptr parentScope() const;
    void setParentScope(const nodeptr &newParentScope);

    value_raw_ptr value() const;
    void setValue(const value_raw_ptr newValue);

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

    value_raw_ptr returnval() const;
    void setReturnval(const value_raw_ptr newReturnval);

    QByteArray raw() const;
    void setRaw(const QByteArray &newRaw);

    declscope declarationMap() const;
    void setDeclarationMap(const declscope newDeclarationMap);

    QStringView typeName() const;
    void setTypeName(const QString &newTypeName);

    QVariantMap parametersMap() const;
    void setParametersMap(const QVariantMap &newParametersMap);

    QStringView referencedId() const;
    void setReferencedId(const QString &newReferencedId);

protected:
    declscope m_declarationMap;
    operatorscope m_operatorMap, m_methodMap;
    nodeptr m_operand,
    m_parentScope,
    m_innerScope;

private: //Private members
    QVariantMap m_parametersMap;
    QByteArray m_raw;
    QString m_name, m_typeName, m_referencedId;
    value_ptr m_value, m_returnval;
    NodeType m_type;
};

} // namespace ServerLang
} // namespace NaiSys

#endif // NAISYS_SERVERLANG_STNODE_H
