#ifndef NAISYS_SERVERLANG_CORE_H
#define NAISYS_SERVERLANG_CORE_H

#include <QString>
#include <QMap>
#include <QVariant>
#include "serverlangnode.h"

namespace NaiSys {
namespace ServerLang {


class Core
{
    /*enum class CoreFunctions{
        Println = 1,
        ReadFile,
        WriteFile,
        String_Replace,
        String_Concat,
        Struct_Modify,
        Struct_Insert,
        Class_Modify,
        DB_Open,
        DB_Close,
        DB_Exec,
        DB_Write
    };
    const QMap<QString, CoreFunctions> m_coreLibMap = {
        {"Println",       CoreFunctions::Println},
        {"FileRead",      CoreFunctions::ReadFile},
        {"FileWrite",     CoreFunctions::WriteFile},
        {"StringReplace", CoreFunctions::String_Replace},
        {"StringConcat",  CoreFunctions::String_Concat},
        {"StructModify",  CoreFunctions::Struct_Modify},
        {"StructInsert",  CoreFunctions::Struct_Insert},
        {"ClassModify",   CoreFunctions::Class_Modify},
        {"DatabaseOpen",  CoreFunctions::DB_Open},
        {"DatabaseClose", CoreFunctions::DB_Close},
        {"DatabaseExec",  CoreFunctions::DB_Exec},
        {"DatabaseWrite", CoreFunctions::DB_Write}
    };*/

private:
    Core() = default;

public:
    static const std::shared_ptr<QVariant>
    exec(const QString &symbol, const QVariantList &args = {}) throw();
    static const void define(const STNode::nodeptr &func = {}) throw();
};

} // namespace ServerLang
} // namespace NaiSys

#endif // NAISYS_SERVERLANG_CORE_H
