#include "serverlangcore.h"
#include <QVariant>
#include <QVariantList>

#include "serverlangfunctions.h"

namespace NaiSys {
namespace ServerLang {

const QVariant Core::exec(const QString &symbol, const QStringList &args) throw()
{
    if(auto _mp = CoreFunctions::functionMap(); _mp.find(symbol) != _mp.end()) {
        auto func = _mp[symbol];
        CoreFunctions::registerParameters(args);
        func();
    }
    return 0;
}

const void Core::define(const QString &symbol, const QStringList &params) throw()
{

}

} // namespace ServerLang
} // namespace NaiSys