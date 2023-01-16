#ifndef NAISYS_SERVERLANG_SYNTAXTREE_H
#define NAISYS_SERVERLANG_SYNTAXTREE_H

#include <algorithm>
#include "serverlangnode.h"

namespace NaiSys {
namespace ServerLang {

class SyntaxTree : public STNode
{
public:
    SyntaxTree();

public://static methods
    static const QString print_tree(const STNode &mp, uint margin_offst = 3);

private:

};

} // namespace ServerLang
} // namespace NaiSys

#endif // NAISYS_SERVERLANG_SYNTAXTREE_H
