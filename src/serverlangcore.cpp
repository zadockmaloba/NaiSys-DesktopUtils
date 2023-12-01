#include "serverlangcore.h"
#include <QVariant>
#include <QVariantList>

#include "serverlangfunctions.h"

namespace NaiSys {
namespace ServerLang {

const value_raw_ptr Core::exec(QStringView symbol, const QVariantMap &args) throw()
{
    if (auto _mp = CoreFunctions::functionMap(); _mp.find(symbol.toString()) != _mp.end()) {
        auto func = _mp[symbol.toString()];
        CoreFunctions::registerParameters(args);
        return func();
    }
    return {};
}

const void Core::define(const STNode::nodeptr &func) throw()
{
    ast_operator opr = [func]()mutable->value_raw_ptr {
        auto const ret = QVariant::fromValue(func);
        return new QVariant(ret);
    };
    CoreFunctions::functionMap().insert({func->name().toString(), opr});
}

} // namespace ServerLang
} // namespace NaiSys
