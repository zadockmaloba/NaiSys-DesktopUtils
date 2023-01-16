#include "serverlangnode.h"

namespace NaiSys {
namespace ServerLang {

const STNode::nodeptr STNode::check_for_declaration(const QString &name)
{
    if(declarationMap().at(name)){
        return declarationMap().at(name);
    }
    return parentScope()->check_for_declaration(name);
}

void STNode::add_declaration(const nodeptr &decl)
{
    m_declarationMap.insert({decl->name(), decl});
}

QString STNode::name() const
{
    return m_name;
}

void STNode::setName(const QString &newName)
{
    m_name = newName;
}

STNode::nodeptr STNode::parentScope() const
{
    return m_parentScope;
}

void STNode::setParentScope(const nodeptr &newParentScope)
{
    m_parentScope = newParentScope;
}

QVariant STNode::value() const
{
    return m_value;
}

void STNode::setValue(const QVariant &newValue)
{
    m_value = newValue;
}

STNode::nodeptr STNode::innerScope() const
{
    return m_innerScope;
}

void STNode::setInnerScope(const nodeptr &newInnerScope)
{
    m_innerScope = newInnerScope;
}

std::map<const QString, const ast_operator > STNode::operatorMap() const
{
    return m_operatorMap;
}

void STNode::setOperatorMap(const std::map<const QString, const ast_operator > &newOperatorMap)
{
    m_operatorMap = newOperatorMap;
}

NodeType STNode::type() const
{
    return m_type;
}

void STNode::setType(NodeType newType)
{
    m_type = newType;
}

std::map<const QString, const ast_operator > STNode::methodMap() const
{
    return m_methodMap;
}

void STNode::setMethodMap(const std::map<const QString, const ast_operator > &newMethodMap)
{
    m_methodMap = newMethodMap;
}

STNode::nodeptr STNode::operand() const
{
    return m_operand;
}

void STNode::setOperand(const nodeptr &newOperand)
{
    m_operand = newOperand;
}

QVariant STNode::returnval() const
{
    return m_returnval;
}

void STNode::setReturnval(const QVariant &newReturnval)
{
    m_returnval = newReturnval;
}

QByteArray STNode::raw() const
{
    return m_raw;
}

void STNode::setRaw(const QByteArray &newRaw)
{
    m_raw = newRaw;
}

STNode::declscope STNode::declarationMap() const
{
    return m_declarationMap;
}

void STNode::setDeclarationMap(const declscope &newDeclarationMap)
{
    m_declarationMap = newDeclarationMap;
}

QString STNode::typeName() const
{
    return m_typeName;
}

void STNode::setTypeName(const QString &newTypeName)
{
    m_typeName = newTypeName;
}

NodeType STNode::get_typecode_from_typename(const QString &tname)
{
    if(tname == "I16") return NodeType::INTEGER;
    else if(tname == "Float") return NodeType::FLOAT;
    else if(tname == "Double") return NodeType::DOUBLE;
    else if(tname == "String") return NodeType::STRING;
    else if(tname == "ByteArray") return NodeType::BYTEARRAY;

    return NodeType::VARIANT;
}

} // namespace ServerLang
} // namespace NaiSys