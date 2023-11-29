#include "serverlangcore.h"
#include <QVariant>
#include <QVariantList>

#include "serverlangfunctions.h"

namespace NaiSys {
namespace ServerLang {

const std::shared_ptr<QVariant> Core::exec(QStringView symbol, const QVariantMap &args) throw()
{
    if(auto _mp = CoreFunctions::functionMap(); _mp.find(symbol) != _mp.end()) {
        auto func = _mp[symbol];
        CoreFunctions::registerParameters(args);
        return func();
    }
    return {};
}

const void Core::define(const STNode::nodeptr &func) throw()
{
    ast_operator opr = [func]()mutable->value_ptr {
        auto const ret = QVariant::fromValue(func);
        return std::make_shared<QVariant>(ret);
    };
    CoreFunctions::functionMap().insert({func->name(), opr});
}

} // namespace ServerLang
} // namespace NaiSys
