#include "serverlangsyntaxtree.h"

namespace NaiSys {
namespace ServerLang {

SyntaxTree::SyntaxTree()
{
    setType(NodeType::SCOPE);
    setName("global_scope");
    setTypeName("Scope");
}

const QString SyntaxTree::print_tree(const STNode &mp, uint margin_offst)
{
    QString ret, offset_str = margin_offst == 0 ? "" : QString(margin_offst,'.');
    ret.append("| "+mp.name().append(" [").append(mp.typeName())+"] \n");
    for(auto const &v : mp.declarationMap())
    {
        ret.append(offset_str+print_tree(*v->second(), margin_offst+3));
    }
    return ret;
}



} // namespace ServerLang
} // namespace NaiSys
