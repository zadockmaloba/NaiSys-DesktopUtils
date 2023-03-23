#include "serverlangparser.h"
#include "serverlanglexer.h"
#include "streamio.h"

namespace NaiSys {
namespace ServerLang {

Parser::Parser()
    : m_globalAST{ new ServerLang::SyntaxTree }
{

}

Parser::Parser(const QString &entryFileName, const QString &pwd)
    : m_fileName{ entryFileName },
      m_workingDir{ pwd },
      m_globalAST{ new ServerLang::SyntaxTree }
{

}

const QRegularExpression Parser::fnmatch = QRegularExpression("\\w+\\([^)]*\\)");
const QRegularExpression Parser::parammatch = QRegularExpression("(?=\")\"[^\"]*\"|[\\w+\\.\\-\\>]*[^\\,\\s\"\\)]");
const QRegularExpression Parser::varmatch = QRegularExpression("var \\w+ \\w+");
const QRegularExpression Parser::importmatch = QRegularExpression("#import\\!\\<[^>]*\\>");
//TODO: Create exprssion for code comments.

void Parser::READ()
{
    QFile f(m_workingDir+m_fileName);
    f.open(QIODevice::ReadOnly);
    m_data = f.readAll();
    f.close();
    auto const tokens = Lexer::analyze(m_data);
    std::for_each(tokens.cbegin(), tokens.cend(), [this](const STNode::nodeptr &v)
    {
        v->setParentScope(m_globalAST);
        m_globalAST->add_declaration(v);
    });
    StreamIO::println(QSTRING_TO_CSTR(
                          SyntaxTree::print_tree(*m_globalAST)
                          ));
}

STNode::nodeptr Parser::globalAST() const
{
    return m_globalAST;
}

} // namespace ServerLang
} // namespace NaiSys
