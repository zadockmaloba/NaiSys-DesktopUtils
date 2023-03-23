#include "serverlangnode.h"

namespace NaiSys {
namespace ServerLang {

const STNode::nodeptr STNode::check_for_declaration(const QString &name)
{
    qDebug() << "Checking for: " << name << " in: " << this->name();
    if(declarationMap().has(name)){
        return declarationMap().at(name);
    }
    else if(parentScope().get() != nullptr)
        return parentScope()->check_for_declaration(name);

    throw "WARNING: Unable to find referenced variable";
    return {};
}

void STNode::add_declaration(const nodeptr &decl)
{
    //FIXME: find out why size() causes segfault
    //qDebug() << m_declarationMap.size();
    m_declarationMap.push_back(decl->name(), decl);
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

operatorscope STNode::operatorMap() const
{
    return m_operatorMap;
}

//Passing by reference causes copy assignment errors in MacOS sdk 13.1
void STNode::setOperatorMap(const operatorscope &newOperatorMap)
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

operatorscope STNode::methodMap() const
{
    return m_methodMap;
}

//Passing by reference causes copy assignment errors in MacOS sdk 13.1
void STNode::setMethodMap(operatorscope newMethodMap)
{
#ifndef Q_OS_OSX
    m_methodMap = std::move(newMethodMap);
#endif
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

//Passing by reference causes copy assignment errors in MacOS sdk 13.1
void STNode::setDeclarationMap(const declscope newDeclarationMap)
{
#ifndef Q_OS_OSX
    m_declarationMap = std::move(newDeclarationMap);
#endif
}

QString STNode::typeName() const
{
    return m_typeName;
}

void STNode::setTypeName(const QString &newTypeName)
{
    m_typeName = newTypeName;
}

QStringList STNode::parametersMap() const
{
    return m_parametersMap;
}

void STNode::setParametersMap(const QStringList &newParametersMap)
{
    m_parametersMap = newParametersMap;
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
