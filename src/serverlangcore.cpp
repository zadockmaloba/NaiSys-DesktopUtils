#include "serverlangcore.h"
#include <QVariant>
#include <QVariantList>

#include "serverlangfunctions.h"

namespace NaiSys {
namespace ServerLang {

const QVariant Core::exec(const QString &symbol, const QStringList &args) throw()
{
    auto const func = CoreFunctions::functionMap().at(symbol);
    CoreFunctions::registerParameters(args);
    func();
    return 0;
}

} // namespace ServerLang
} // namespace NaiSys
