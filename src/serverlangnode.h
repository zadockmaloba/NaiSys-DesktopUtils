#ifndef NAISYS_SERVERLANG_STNODE_H
#define NAISYS_SERVERLANG_STNODE_H

#include <QString>
#include <QVariant>
#include <QByteArray>
#include <map>

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
    VARIANT,
    STRUCT,
    CLASS,
    HOOK,
    FUNCTION,
    SCOPE,
    IF_STATEMENT,
    MATCH_STATEMENT,
    BINARY_EXPRESSION,
    RETURN_EXPRESSION,
    CALL_EXPRESSION
};

typedef std::function<void ()> ast_operator;


class STNode
{
public://Typedefs
    typedef std::shared_ptr<STNode> nodeptr;
    typedef std::map<const QString, const nodeptr> declscope;

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

    std::map<const QString, const ast_operator> operatorMap() const;
    void setOperatorMap(const std::map<const QString, const ast_operator > &newOperatorMap);

    NodeType type() const;
    void setType(NodeType newType);

    std::map<const QString, const std::function<void ()> > methodMap() const;
    void setMethodMap(const std::map<const QString, const std::function<void ()> > &newMethodMap);

    nodeptr operand() const;
    void setOperand(const nodeptr &newOperand);

    QVariant returnval() const;
    void setReturnval(const QVariant &newReturnval);

    QByteArray raw() const;
    void setRaw(const QByteArray &newRaw);

    declscope declarationMap() const;
    void setDeclarationMap(const declscope &newDeclarationMap);

    QString typeName() const;
    void setTypeName(const QString &newTypeName);

private: //Private members
    declscope m_declarationMap;
    nodeptr m_operand,
    m_parentScope,
    m_innerScope;
    QByteArray m_raw;
    QString m_name, m_typeName;
    QVariant m_value = QByteArray(),
    m_returnval = QByteArray();
    std::map<const QString, const ast_operator> m_operatorMap, m_methodMap;
    NodeType m_type;
};

} // namespace ServerLang
} // namespace NaiSys

#endif // NAISYS_SERVERLANG_STNODE_H
