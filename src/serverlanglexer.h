#ifndef SERVERLANGLEXER_H
#define SERVERLANGLEXER_H

#include <QString>
#include <QRegularExpression>
#include <vector>
#include "serverlangnode.h"
#include "serverlangtypes.h"


#define __MATCH_ITERATOR(x,y) for(auto &v : x)\
{\
    auto const __obj = STNode::nodeptr(new y);\
    __obj->setName(QString::number(rand()));\
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
        auto const ret_expr = find_regex_match(returnexpression_capture, m_lexicalScope);
        m_lexicalScope.remove(returnexpression_capture);
        auto const func_call = find_regex_match(function_call, m_lexicalScope);
        m_lexicalScope.remove(function_call);
        auto const var_dcl = find_regex_match(variable_decl, m_lexicalScope);
        m_lexicalScope.remove(variable_decl);

        __MATCH_ITERATOR(hks_dcl, Hook);
        __MATCH_ITERATOR(cls_dcl, Class);
        __MATCH_ITERATOR(cls_dcl_i, Class);
        __MATCH_ITERATOR(func_dcl, Function);
        __MATCH_ITERATOR(strct_dcl, Struct);
        __MATCH_ITERATOR(strct_dcl_i, Struct);
        __MATCH_ITERATOR(ret_expr, ReturnExpression);
        __MATCH_ITERATOR(func_call, CallExpression);
        __MATCH_ITERATOR(var_dcl, Variant);

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
        case NodeType::CLASS: {
            auto temp = QString(node->raw());
            auto const _body = scope_capture
                    .match(temp).captured();
            temp.remove(_body);
            auto const _name = temp.remove("class ")
                    .remove("=").remove(";").trimmed();
            node->setName(_name);
            auto const decls = analyze(_body);
            for(auto &v : decls)
                node->add_declaration(v);
            break;
        }
        case NodeType::HOOK: {
            auto temp = QString(node->raw());
            auto const _body = scope_capture
                    .match(temp).captured();
            temp.remove(_body);
            auto const _name = temp.remove(";").trimmed();
            node->setName(_name);
            auto const decls = analyze(_body);
            for(auto &v : decls)
                node->add_declaration(v);
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
            auto spec = _name.split(":");
            node->setName(spec.at(0).trimmed());
            auto const decls = analyze(_body);
            for(auto &v : decls)
                node->add_declaration(v);
            break;
        }
        case NodeType::VARIANT: {
            auto temp = QString(node->raw());
            auto const _body = varvalue_capture
                    .match(temp).captured()
                    .remove("=").trimmed();
            auto const _name = temp.remove(varvalue_capture).remove(";")
                    .remove("var").trimmed();
            auto spec = _name.split(":");
            node->setName(spec.at(0).trimmed());
            node->setValue(_body);
            if(spec.size() >= 2)
            {
                node->setTypeName(spec.at(1).trimmed());
                node->setType(STNode::get_typecode_from_typename(node->typeName()));
            }
            break;
        }
        default:
            break;
        }
    }

private://static members
    static const QRegularExpression hook_decl;
    static const QRegularExpression function_decl;
    static const QRegularExpression function_call;
    static const QRegularExpression class_decl;
    static const QRegularExpression class_decl_inner;
    static const QRegularExpression struct_decl;
    static const QRegularExpression struct_decl_inner;
    static const QRegularExpression variable_decl;
    static const QRegularExpression parameters_capture;
    static const QRegularExpression scope_capture;
    static const QRegularExpression varvalue_capture;
    static const QRegularExpression binexpression_capture;
    static const QRegularExpression returnexpression_capture;

};

inline const QRegularExpression Lexer::hook_decl =
        QRegularExpression{"@\\s*\\/[\\*\\@\\-]*[\\w*\\@\\-\\!\\s\\/\\#]*\\s*[=\\s]*\\{[\\s\\S]*?\\}\\;"};
inline const QRegularExpression Lexer::function_decl =
        QRegularExpression{"def\\s+\\w+\\s*\\([\\s\\S]*?\\)*\\s*\\{[\\s\\S]*?\\}"};
inline const QRegularExpression Lexer::function_call =
        QRegularExpression{"call\\s+\\w+[\\w\\:]*\\s*\\([\\s\\S]*\\)+\\;"};
inline const QRegularExpression Lexer::class_decl =
        QRegularExpression{"class\\s+\\w+[=\\s]*\\{[\\s\\S]*?\\}\\;"};
inline const QRegularExpression Lexer::class_decl_inner =
        QRegularExpression{"class\\s+\\w+[=\\s]*\\{[\\s\\S]*?\\}"};
inline const QRegularExpression Lexer::struct_decl =
        QRegularExpression{"struct\\s+\\w+[=\\s]*\\{[\\s\\S]*?\\}\\;"};
inline const QRegularExpression Lexer::struct_decl_inner =
        QRegularExpression{"struct\\s+\\w+[=\\s]*\\{[\\s\\S]*?\\}"};
inline const QRegularExpression Lexer::variable_decl =
        QRegularExpression{"var\\s+\\w+\\s*(\\:\\s*\\w+\\s*)*\\=[\\s\\S]*?\\;"};
inline const QRegularExpression Lexer::scope_capture =
        QRegularExpression{"{[\\s\\S]*\\}"};
inline const QRegularExpression Lexer::varvalue_capture =
        QRegularExpression{"(?==)\\=[\\s\\S]*(?=;)"};
inline const QRegularExpression Lexer::binexpression_capture =
        QRegularExpression{"[\\s\\S]*[\\+\\-\\*\\/][\\s\\S]*\\;"};
inline const QRegularExpression Lexer::returnexpression_capture =
        QRegularExpression{"return\\:\\=[\\s\\S]*\\;"};

}
}

#undef __MATCH_ITERATOR
#endif // SERVERLANGLEXER_H
