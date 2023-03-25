#include "serverlangcore.h"
#include <QVariant>
#include <QVariantList>

#include "serverlangfunctions.h"

namespace NaiSys {
namespace ServerLang {

const std::shared_ptr<QVariant>
Core::exec(const QString &symbol, const QVariantList &args) throw()
{
    if(auto _mp = CoreFunctions::functionMap(); _mp.find(symbol) != _mp.end()) {
        auto func = _mp[symbol];
        CoreFunctions::registerParameters(args);
        return func();
    }
    return {};
}

const void Core::define(const QString &symbol, const QVariantList &params) throw()
{

}

} // namespace ServerLang
} // namespace NaiSys
