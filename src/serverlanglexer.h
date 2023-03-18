#ifndef SERVERLANGLEXER_H
#define SERVERLANGLEXER_H

#include <QString>
#include <QRegularExpression>
#include <vector>
#include <stdlib.h>
#include "serverlangnode.h"
#include "serverlangtypes.h"


#define __MATCH_ITERATOR(x,y) for(auto &v : x)\
{\
    auto const __obj = STNode::nodeptr(new y);\
    __obj->setName(QString::number(arc4random()));\
    __obj->setRaw(v.toUtf8());\
    node_recursive_analysis(__obj);\
    m_tokenList.push_back(__obj);\
}\

namespace NaiSys {
namespace ServerLang {

class Lexer
{
public:
    Lexer() = default;

public:
    static const std::vector<STNode::nodeptr> analyze(const QString &data)
    {
        QString m_lexicalScope = data;
        std::vector<STNode::nodeptr> m_tokenList;

        auto const py_scope = find_regex_match(py_scope_capture, m_lexicalScope);
        m_lexicalScope.remove(py_scope_capture);

        auto const hks_dcl = find_regex_match(hook_decl, m_lexicalScope);
        m_lexicalScope.remove(hook_decl);
        auto const cls_dcl = find_regex_match(class_decl, m_lexicalScope);
        m_lexicalScope.remove(class_decl);
        auto const cls_dcl_i = find_regex_match(class_decl_inner, m_lexicalScope);
        m_lexicalScope.remove(class_decl_inner);
        auto const func_dcl = find_regex_match(function_decl, m_lexicalScope);
        m_lexicalScope.remove(function_decl);
        auto const strct_dcl = find_regex_match(struct_decl, m_lexicalScope);
        m_lexicalScope.remove(struct_decl);
        auto const strct_dcl_i = find_regex_match(struct_decl_inner, m_lexicalScope);
        m_lexicalScope.remove(struct_decl_inner);
        auto const arr_dcl = find_regex_match(array_decl, m_lexicalScope);
        m_lexicalScope.remove(array_decl);
        auto const var_dcl = find_regex_match(variable_decl, m_lexicalScope);
        m_lexicalScope.remove(variable_decl);
        auto const ret_expr = find_regex_match(returnexpression_capture, m_lexicalScope);
        m_lexicalScope.remove(returnexpression_capture);
        auto const field_acc_i = find_regex_match(field_accessor_internal, m_lexicalScope);
        m_lexicalScope.remove(field_accessor_internal);
        auto const func_call = find_regex_match(function_call, m_lexicalScope);
        m_lexicalScope.remove(function_call);
        auto const string_literals = find_regex_match(string_literal_capture, m_lexicalScope);
        m_lexicalScope.remove(string_literal_capture);
        auto const numeric_literals = find_regex_match(numeric_literal_capture, m_lexicalScope);
        m_lexicalScope.remove(numeric_literal_capture);
        auto const var_id = find_regex_match(var_identifier_capture, m_lexicalScope);
        m_lexicalScope.remove(var_identifier_capture);

        __MATCH_ITERATOR(py_scope, PyScope);
        __MATCH_ITERATOR(hks_dcl, Hook);
        __MATCH_ITERATOR(cls_dcl, Class);
        __MATCH_ITERATOR(cls_dcl_i, Class);
        __MATCH_ITERATOR(func_dcl, Function);
        __MATCH_ITERATOR(strct_dcl, Struct);
        __MATCH_ITERATOR(strct_dcl_i, Struct);
        __MATCH_ITERATOR(arr_dcl, Array);
        __MATCH_ITERATOR(var_dcl, Variant);
        __MATCH_ITERATOR(ret_expr, ReturnExpression);
        __MATCH_ITERATOR(field_acc_i, Variant);//TODO
        __MATCH_ITERATOR(func_call, CallExpression);
        __MATCH_ITERATOR(string_literals, Literal);
        __MATCH_ITERATOR(numeric_literals, Literal);
        __MATCH_ITERATOR(var_id, VariableExpression);

        qDebug() << "[SERVERLANG_LEXER]: Number of Tokens captured: "
                 << m_tokenList.size();
        return m_tokenList;
    }

private://methods
    static const QStringList find_regex_match(const QRegularExpression &exp, const QString &str)
    {
        QStringList ret;
        auto itr = exp.globalMatch(str);
        while(itr.hasNext()){
            auto const mtch = itr.next().captured();
            ret.append(mtch);
        }
        return ret;
    }
    static void node_recursive_analysis(const STNode::nodeptr &node){
        switch (node->type()) {
        case NodeType::PY_SCOPE: {
            auto temp = QString(node->raw());
            auto const _body = scope_capture
                    .match(temp).captured().remove(0, 1).chopped(1);
            node->setValue(_body);
            node->setName(QString::number(arc4random())+"://Python::Scope");
            break;
        }
        case NodeType::LITERAL: {
            node->setValue(node->raw());
            node->setName(QString::number(arc4random())+"://Literal");
            break;
        }
        case NodeType::CLASS: {
            auto temp = QString(node->raw());
            auto const _body = scope_capture
                    .match(temp).captured();
            temp.remove(_body);
            auto const _name = temp.remove("class ")
                    .remove("=").remove(";").trimmed();
            node->setName(_name);
            auto const decls = analyze(_body);
            for(auto &v : decls) {
                v->setParentScope(node);
                node->add_declaration(v);
            }
            break;
        }
        case NodeType::HOOK: {
            auto temp = QString(node->raw());
            auto const _body = scope_capture
                    .match(temp).captured();
            temp.remove(_body);
            auto const _name = temp
                    .remove(0, 1)
                    .remove(";").trimmed();
            node->setName(_name);
            auto const decls = analyze(_body);

            auto const _hk_header = STNode::nodeptr(new String);
            auto const _hk_body = STNode::nodeptr(new Variant);

            _hk_header->setName("Header");
            _hk_body->setName("Body");

            _hk_header->setParentScope(node);
            _hk_body->setParentScope(node);

            node->add_declaration(_hk_header);
            node->add_declaration(_hk_body);

            for(auto &v : decls) {
                v->setParentScope(node);
                node->add_declaration(v);
            }
            break;
        }
        case NodeType::STRUCT: {
            auto temp = QString(node->raw());
            auto const _body = scope_capture
                    .match(temp).captured();
            temp.remove(_body);
            auto const _name = temp.remove("struct ")
                    .remove("=").remove(";").trimmed();
            node->setName(_name);
            node->setValue(QJsonDocument::fromJson(_body.toUtf8()).object());
            break;
        }
        case NodeType::FUNCTION: {
            auto temp = QString(node->raw());
            auto const _body = scope_capture
                    .match(temp).captured();
            temp.remove(scope_capture);
            auto _name = temp.remove("def ");
            auto const _params = brackets_capture
                    .match(_name).captured();
            _name.remove(brackets_capture);
            auto spec = _name.split(":");
            node->setName(spec.at(0).trimmed());

            auto const p =analyze(_params);
            auto const ArgObj = STNode::nodeptr(new STNode);
            ArgObj->setType(NodeType::SCOPE);
            ArgObj->setTypeName("Scope");
            ArgObj->setName("Args");
            ArgObj->setParentScope(node);
            node->add_declaration(ArgObj);

            for(auto &v: p)
                ArgObj->add_declaration(v);

            auto const decls = analyze(_body);
            for(auto &v : decls)
                node->add_declaration(v);
            break;
        }
        case NodeType::ARRAY: {
            auto temp = QString(node->raw());
            auto const _body = scope_capture
                    .match(temp).captured()
                    .remove("{")
                    .remove("}");
            temp.remove(_body)
                    .remove("{")
                    .remove("}");
            auto _bracket = squarebrackets_capture
                    .match(temp).captured();
            temp.remove(_bracket);
            auto const _name = temp.remove("var ")
                    .remove("=").remove(";").trimmed();
            auto spec = _name.split(":");
            node->setName(spec.at(0).trimmed());
            node->setValue(_body);

            spec.size() >= 2 ? node->setTypeName("Array::"+spec.at(1).trimmed()) :
                               node->setTypeName("Array::Variant");

            auto const arr_length = _bracket
                    .remove('[')
                    .remove(']')
                    .toInt();
            auto const _elements = analyze(_body);

            if(arr_length > 0){
                for(int i=0; i<arr_length; ++i)
                {
                    STNode::nodeptr nd;
                    i < _elements.size() ?
                        nd = STNode::nodeptr(_elements.at(i)) :
                        nd = STNode::nodeptr(new Literal("0x00", QString::number(i)));
                    nd->setName(QString::number(i)+"://"+nd->raw());
                    nd->setParentScope(node);
                    node->add_declaration(nd);
                }
            }
            else {
                for(int i=0; i<_elements.size(); ++i)
                {
                    auto nd = STNode::nodeptr(_elements.at(i));
                    nd->setName(QString::number(i)+"://"+nd->raw());
                    nd->setParentScope(node);
                    node->add_declaration(nd);
                }
            }
            break;
        }
        case NodeType::VARIANT: {
            auto temp = QString(node->raw());
            auto const _body = varvalue_capture
                    .match(temp).captured()
                    .remove("=").trimmed();
            auto const _name = temp.remove(varvalue_capture)
                    .remove(";")
                    .remove(QRegularExpression{"^var"})
                    .trimmed();
            auto spec = _name.split(":");
            node->setName(spec.at(0).trimmed());
            node->setValue(_body);
            if(spec.size() >= 2)
            {
                node->setTypeName(spec.at(1).trimmed());
                node->setType(STNode::get_typecode_from_typename(node->typeName()));
            }
            auto const decls = analyze(_body);
            qDebug() << "VARIANT_RAW_DATA: "<< _body;
            for(auto &v : decls) {
                v->setParentScope(node);
                node->add_declaration(v);
            }
            break;
        }
        case NodeType::VARIABLE_EXPRESSION: {
            auto temp = QString(node->raw());
            auto const _name = temp.remove("$");
            node->setName(QString::number(arc4random())+"://"+_name);
            node->setValue(_name);
            break;
        }
        case NodeType::CALL_EXPRESSION: {
            auto temp = QString(node->raw());
            auto const _args = brackets_capture.match(temp)
                    .captured().trimmed();
            auto const _name = temp.remove(brackets_capture);
            node->setName(QString::number(arc4random())+"://"+_name);

            auto const decls = analyze(_args);
            QStringList _params;
            for(auto &v : decls) {
                node->add_declaration(v);
                _params << v->value().toString();
                qDebug() << "PARAMETER_VAL: " << v->value().toString();
            }
            node->setParametersMap(_params);
            qDebug() << "Arguments: " << node->parametersMap();

            break;
        }
        default:
            break;
        }
    }

private://static members
    static const QRegularExpression py_scope_capture;
    static const QRegularExpression hook_decl;
    static const QRegularExpression function_decl;
    static const QRegularExpression function_call;
    static const QRegularExpression class_decl;
    static const QRegularExpression class_decl_inner;
    static const QRegularExpression struct_decl;
    static const QRegularExpression struct_decl_inner;
    static const QRegularExpression variable_decl;
    static const QRegularExpression array_decl;
    static const QRegularExpression parameters_capture;
    static const QRegularExpression scope_capture;
    static const QRegularExpression varvalue_capture;
    static const QRegularExpression binexpression_capture;
    static const QRegularExpression returnexpression_capture;
    static const QRegularExpression squarebrackets_capture;
    static const QRegularExpression brackets_capture;
    static const QRegularExpression var_identifier_capture;
    static const QRegularExpression string_literal_capture;
    static const QRegularExpression numeric_literal_capture;
    static const QRegularExpression field_accessor_internal;
    static const QRegularExpression field_accessor_external;
};

inline const QRegularExpression Lexer::py_scope_capture =
        QRegularExpression{"\\!py\\{[\\s\\S]*?\\}\\s*(\\([\\s\\S]*?\\))*\\;\\!"};
inline const QRegularExpression Lexer::hook_decl =
        QRegularExpression{"@\\s*\\/[\\*\\@\\-]*[\\w*\\@\\-\\!\\s\\/\\#]*\\s*[=\\s]*\\{[\\s\\S]*?\\}\\;"};
inline const QRegularExpression Lexer::function_decl =
        QRegularExpression{"def\\s+\\w+\\s*\\([\\s\\S]*?\\)*\\s*\\{[\\s\\S]*?\\}"};
inline const QRegularExpression Lexer::function_call =
        QRegularExpression{"(\\w+\\:\\:)*\\w+\\s*\\([\\s\\S]*?\\)"};
inline const QRegularExpression Lexer::class_decl =
        QRegularExpression{"class\\s+\\w+[=\\s]*\\{[\\s\\S]*?\\}\\;"};
inline const QRegularExpression Lexer::class_decl_inner =
        QRegularExpression{"class\\s+\\w+[=\\s]*\\{[\\s\\S]*?\\}"};
inline const QRegularExpression Lexer::struct_decl =
        QRegularExpression{"struct\\s+\\w+[=\\s]*\\{[\\s\\S]*?\\}\\;"};
inline const QRegularExpression Lexer::struct_decl_inner =
        QRegularExpression{"struct\\s+\\w+[=\\s]*\\{[\\s\\S]*?\\}"};
inline const QRegularExpression Lexer::variable_decl =
        QRegularExpression{"var\\s+\\w+\\s*(\\:\\s*\\w+\\s*)*(\\=[\\s\\S]*?\\;)*"};
inline const QRegularExpression Lexer::scope_capture =
        QRegularExpression{"{[\\s\\S]*\\}"};
inline const QRegularExpression Lexer::varvalue_capture =
        QRegularExpression{"(?==)\\=[\\s\\S]*(?=;)"};
inline const QRegularExpression Lexer::binexpression_capture =
        QRegularExpression{"[\\s\\S]*?[\\+\\-\\*\\/][\\s\\S]*?\\;"};
inline const QRegularExpression Lexer::returnexpression_capture =
        QRegularExpression{"return\\:\\=[\\s\\S]*\\;"};
inline const QRegularExpression Lexer::array_decl =
        QRegularExpression{"var\\s\\w+\\[[\\s\\S]*?\\]\\s*(\\:\\s*\\w+\\s*)*\\=\\s*\\{[\\s\\S]*?\\}\\;"};
inline const QRegularExpression Lexer::squarebrackets_capture =
        QRegularExpression{"\\[\\d*\\]"};
inline const QRegularExpression Lexer::brackets_capture =
        QRegularExpression{"\\([\\s\\S]*?\\)"};
inline const QRegularExpression Lexer::var_identifier_capture =
        QRegularExpression{"\\$\\w+(\\s*[\\=\\-\\>\\.\\:]\\s*[\\s\\S]*?\\;)*"};
inline const QRegularExpression Lexer::string_literal_capture =
        QRegularExpression{"\"[\\s\\S]*?\""};
inline const QRegularExpression Lexer::numeric_literal_capture =
        QRegularExpression{"\\d+(\\.\\d)*"};
inline const QRegularExpression Lexer::field_accessor_internal =
        QRegularExpression{"\\.\\w+(\\s*=\\s*[\\s\\S]*\\;)*"};
inline const QRegularExpression Lexer::field_accessor_external =
        QRegularExpression{};

}
}

#undef __MATCH_ITERATOR
#endif // SERVERLANGLEXER_H
