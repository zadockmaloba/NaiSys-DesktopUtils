#include "serverlangparser.h"
#include "serverlanglexer.h"
#include "streamio.h"

namespace NaiSys {
namespace ServerLang {

parser::parser()
{

}

parser::parser(const QStringView &entryFileName, const QString &pwd)
    : m_fileName{ entryFileName.toString() },
      m_workingDir{ pwd }
{

}

const QRegularExpression parser::fnmatch = QRegularExpression("\\w+\\([^)]*\\)");
const QRegularExpression parser::parammatch = QRegularExpression("(?=\")\"[^\"]*\"|[\\w+\\.\\-\\>]*[^\\,\\s\"\\)]");
const QRegularExpression parser::varmatch = QRegularExpression("var \\w+ \\w+");
const QRegularExpression parser::importmatch = QRegularExpression("#import\\!\\<[^>]*\\>");

void parser::READ()
{
    QFile f(m_workingDir+m_fileName);
    f.open(QIODevice::ReadOnly);
    m_data = f.readAll();
    f.close();
    auto const tokens = Lexer::analyze(m_data);
    std::for_each(tokens.cbegin(), tokens.cend(), [this](const STNode::nodeptr &v)
    {
        m_globalAST.add_declaration(v);
    });
    StreamIO::println(QSTRING_TO_CSTR(
                          SyntaxTree::print_tree(m_globalAST)
                          ));
}

} // namespace ServerLang
} // namespace NaiSys
