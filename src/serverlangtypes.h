#ifndef SERVERLANGTYPES_H
#define SERVERLANGTYPES_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QList>
#include "serverlangnode.h"

namespace NaiSys {
namespace ServerLang {

struct Array : STNode {
    Array(const QByteArray &data = {})
    {
        setRaw(data);
        setType(NodeType::ARRAY);
        setTypeName("Array");
    }
};

struct Bool : STNode {

};

struct I16 : STNode
{
    I16(const QByteArray &data)
    {
        setRaw(data);
        setType(NodeType::INTEGER);
        setTypeName("I16");
        setOperatorMap({
                         {"=", assign},
                         {"+", add},
                         {"-", sub},
                         {"*", mul},
                         {"/", div}
                     });
    }
private:
    const ast_operator assign = [this]()mutable->value_ptr{
        this->setValue(operand()->value());
        return {};
    };
    const ast_operator add = [this]()mutable->value_ptr{
        auto const lhs = this->value()->toInt();
        auto const rhs = this->operand()->value()->toInt();
        this->setReturnval(value_ptr{new QVariant(lhs+rhs)});
        return {};
    };
    const ast_operator sub = [this]()mutable->value_ptr{
        auto const lhs = this->value()->toInt();
        auto const rhs = this->operand()->value()->toInt();
        this->setReturnval(value_ptr{new QVariant(lhs-rhs)});
        return {};
    };
    const ast_operator mul = [this]()mutable->value_ptr{
        auto const lhs = this->value()->toInt();
        auto const rhs = this->operand()->value()->toInt();
        this->setReturnval(value_ptr{new QVariant(lhs*rhs)});
        return {};
    };
    const ast_operator div = [this]()mutable->value_ptr{
        auto const lhs = this->value()->toInt();
        auto const rhs = this->operand()->value()->toInt();
        this->setReturnval(value_ptr{new QVariant(lhs/rhs)});
        return {};
    };
};

struct Double : STNode
{
    Double(const QByteArray &data)
    {
        setRaw(data);
        setType(NodeType::DOUBLE);
        setTypeName("Double");
        setOperatorMap({
                         {"=", assign},
                         {"+", add},
                         {"-", sub},
                         {"*", mul},
                         {"/", div}
                     });
    }
private:
    const ast_operator assign = [this]()mutable->value_ptr{
        this->setValue(operand()->value());
        return {};
    };
    const ast_operator add = [this]()mutable->value_ptr{
        auto const lhs = this->value()->toDouble();
        auto const rhs = this->operand()->value()->toDouble();
        this->setReturnval(value_ptr{new QVariant(lhs+rhs)});
        return {};
    };
    const ast_operator sub = [this]()mutable->value_ptr{
        auto const lhs = this->value()->toDouble();
        auto const rhs = this->operand()->value()->toDouble();
        this->setReturnval(value_ptr{new QVariant(lhs-rhs)});
        return {};
    };
    const ast_operator mul = [this]()mutable->value_ptr{
        auto const lhs = this->value()->toDouble();
        auto const rhs = this->operand()->value()->toDouble();
        this->setReturnval(value_ptr{new QVariant(lhs*rhs)});
        return {};
    };
    const ast_operator div = [this]()mutable->value_ptr{
        auto const lhs = this->value()->toDouble();
        auto const rhs = this->operand()->value()->toDouble();
        this->setReturnval(value_ptr{new QVariant(lhs/rhs)});
        return {};
    };
};

struct Float : STNode
{
    Float(const QByteArray &data)
    {
        setRaw(data);
        setType(NodeType::FLOAT);
        setTypeName("Float");
        setOperatorMap({
                         {"=", assign},
                         {"+", add},
                         {"-", sub},
                         {"*", mul},
                         {"/", div}
                     });
    }
private:
    const ast_operator assign = [this]()mutable->value_ptr{
        this->setValue(operand()->value());
        return {};
    };
    const ast_operator add = [this]()mutable->value_ptr{
        auto const lhs = this->value()->toFloat();
        auto const rhs = this->operand()->value()->toFloat();
        this->setReturnval(value_ptr{new QVariant(lhs+rhs)});
        return {};
    };
    const ast_operator sub = [this]()mutable->value_ptr{
        auto const lhs = this->value()->toFloat();
        auto const rhs = this->operand()->value()->toFloat();
        this->setReturnval(value_ptr{new QVariant(lhs-rhs)});
        return {};
    };
    const ast_operator mul = [this]()mutable->value_ptr{
        auto const lhs = this->value()->toFloat();
        auto const rhs = this->operand()->value()->toFloat();
        this->setReturnval(value_ptr{new QVariant(lhs*rhs)});
        return {};
    };
    const ast_operator div = [this]()mutable->value_ptr{
        auto const lhs = this->value()->toFloat();
        auto const rhs = this->operand()->value()->toFloat();
        this->setReturnval(value_ptr{new QVariant(lhs/rhs)});
        return {};
    };
};

struct ByteArray : STNode
{
    ByteArray(const QByteArray &data = {})
    {
        setRaw(data);
        setType(NodeType::BYTEARRAY);
        setTypeName("ByteArray");
        setOperatorMap({
                         {"=", assign},
                         {"+", concat}
                       });
    }
private:
    const ast_operator assign = [this]()mutable->value_ptr{
        this->setValue(operand()->value());
        return {};
    };
    const ast_operator concat = [this]()mutable->value_ptr{
        this->setValue(value_ptr{new QVariant(value()->toByteArray()
                                 +operand()->value()->toByteArray())});
        return {};
    };
};

struct String : STNode
{
    String(const QByteArray &data = {})
    {
        setRaw(data);
        setType(NodeType::STRING);
        setTypeName("String");
        setOperatorMap({
                         {"=", assign},
                         {"+", concat}
                       });
    }
private:
    const ast_operator assign = [this]()mutable->value_ptr{
        this->setReturnval(operand()->value());
        return {};
    };
    const ast_operator concat = [this]()mutable->value_ptr{
        this->setReturnval(value_ptr{ new QVariant(value()->toString()
                                      +operand()->value()->toString())});
        return {};
    };
};

struct Literal : STNode
{
    Literal(const QByteArray &data = {}, const QString &_id = QString::number(rand()) )
    {
        setRaw(data);
        setType(NodeType::LITERAL);
        setTypeName("Literal");
        setName(_id+" val: "+data);
    }
};
\
struct Variant : STNode
{
    Variant(const QByteArray &data = {})
    {
        setRaw(data);
        setType(NodeType::VARIANT);
        setTypeName("Variant");
        setOperatorMap({
                         {"=", assign},
                         {"+", concat}
                       });
    }

public:
    NodeType inferredType() const
    {
        return m_inferredType;
    }
    void setInferredType(NodeType newInferredType)
    {
        m_inferredType = newInferredType;
    }

    QString inferredTypeName() const
    {
        return m_inferredTypeName;
    }
    void setInferredTypeName(const QString &newInferredTypeName)
    {
        m_inferredTypeName = newInferredTypeName;
    }

private:
    NodeType m_inferredType;
    QString m_inferredTypeName;

private:
    const ast_operator assign = [this]()mutable->value_ptr{
        this->setReturnval(operand()->value());
        return {};
    };
    const ast_operator concat = [this]()mutable->value_ptr{
        this->setReturnval(value_ptr{ new QVariant(value()->toString()
                                      +operand()->value()->toString())});
        return {};
    };
};

struct Struct : STNode
{
    Struct(const QByteArray &data = {})
    {
        setRaw(data);
        setType(NodeType::STRUCT);
        setTypeName("Struct");
        setOperatorMap({
                           {"=", assign},
                           {"->", access}
                       });
        setMethodMap({
                         {"insert", insert}
                     });

        m_data = QJsonDocument::fromJson(this->raw()).object();
    }
    const QString checkFor(const QString &key)
    {
        return m_data.value(key).toString();
    }
private://members
    QJsonObject m_data;

private:
    const ast_operator assign = [this]()mutable->value_ptr{
        this->setValue(operand()->value());
        return {};
    };
    const ast_operator access = [this]()mutable->value_ptr{
        this->setReturnval(value_ptr{ new QVariant(checkFor(operand()->name()))});
        return {};
    };
    const ast_operator insert = [this]()mutable->value_ptr{
        m_data.insert(operand()->name(), operand()->value()->toString());
        return {};
    };
};

struct Class : STNode
{
    Class(const QByteArray &data = {})
    {
        setRaw(data);
        setType(NodeType::CLASS);
        setTypeName("Class");
        setOperatorMap({
                           {"=", assign},
                           {"->", access}
                       });
    }
private:
    const ast_operator assign = [this]()mutable->value_ptr{
        this->setValue(operand()->value());
        return {};
    };
    const ast_operator access = [this]()mutable->value_ptr{
        this->setReturnval(value_ptr{ new QVariant(operand()->name())});
        return {};
    };
};

struct Hook : STNode
{
    Hook(const QByteArray &data = {})
    {
        setRaw(data);
        setType(NodeType::HOOK);
        setTypeName("Hook");
        setOperatorMap({
                           {"()", exec}
                       });
    }
public://public members
    ast_operator exec;
    ast_operator declare;

    const QStringList &parameters() const
    {
        return m_parameters;
    }
    void setParameters(const QStringList &newParameters)
    {
        m_parameters = newParameters;
        MAP_PARAMS_TO_ARGS();
    }
    const QStringList &arguments() const
    {
        return m_arguments;
    }
    void setArguments(const QStringList &newArguments)
    {
        m_arguments = newArguments;
    }

private://private members
    QStringList m_parameters, m_arguments;
private://private methods
    void MAP_PARAMS_TO_ARGS()
    {

    }
};

struct Function : STNode
{
    Function(const QByteArray &data = {})
    {
        setRaw(data);
        setType(NodeType::FUNCTION);
        setTypeName("Function");
        setOperatorMap({
                           {"()", exec}
                       });
    }
public://public members
    ast_operator exec;
    ast_operator declare;

    const QVariantList &parameters() const
    {
        return m_parameters;
    }
    void setParameters(const QVariantList &newParameters)
    {
        m_parameters = newParameters;
        MAP_PARAMS_TO_ARGS();
    }
    const QVariantList &arguments() const
    {
        return m_arguments;
    }
    void setArguments(const QVariantList &newArguments)
    {
        m_arguments = newArguments;
    }

private://private members
    QVariantList m_parameters, m_arguments;
private://private methods
    void MAP_PARAMS_TO_ARGS()
    {

    }
};

struct BinaryExpression : STNode
{
    BinaryExpression(const QByteArray &data = {})
    {
        setRaw(data);
        setType(NodeType::BINARY_EXPRESSION);
        setTypeName("BinaryExpression");
    }
public://public members

};

struct ReturnExpression : STNode
{
    ReturnExpression(const QByteArray &data = {})
    {
        setRaw(data);
        setType(NodeType::RETURN_EXPRESSION);
        setTypeName("ReturnExression");
    }
};

struct CallExpression : STNode
{
    CallExpression(const QByteArray &data = {})
    {
        setRaw(data);
        setType(NodeType::CALL_EXPRESSION);
        setTypeName("CallExpression");
    }
};

struct VariableExpression : STNode
{
    VariableExpression(const QByteArray &data = {})
    {
        setRaw(data);
        setType(NodeType::VARIABLE_EXPRESSION);
        setTypeName("VariableExpression");
    }
};

struct Scope : STNode
{
    Scope(const QByteArray &data = {})
    {
        setRaw(data);
        setType(NodeType::SCOPE);
        setTypeName("Scope");
    }
};

struct PyScope : STNode
{
    PyScope(const QByteArray &data = {})
    {
        setRaw(data);
        setType(NodeType::PY_SCOPE);
        setTypeName("Scope::Python");
    }
};

struct StructAccessor : STNode
{
    StructAccessor(const QByteArray &data = {})
    {
        setRaw(data);
        setType(NodeType::STRUCT_ACCESSOR);
        setTypeName("StructAccessor");
    }
};

struct NamedParameter : STNode
{
    NamedParameter(const QByteArray &data = {})
    {
        setRaw(data);
        setType(NodeType::PARAMETER_LABEL);
        setTypeName("NamedParameter");
    }
};

}
}

#endif // SERVERLANGTYPES_H
