#ifndef NAISYS_NAISYSXLSX_H
#define NAISYS_NAISYSXLSX_H

#include "NaiSys_DesktopUtils_global.h"

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>

#include "Xlsx/Workbook.h"
#include "Xlsx/Worksheet.h"

#ifdef QT_CORE_LIB
#include <QDateTime>
#endif


namespace NaiSys {

class NAISYSDESKTOPUTILS_EXPORT NaiSysXLSX : public QObject
{
    Q_OBJECT
public:
    NaiSysXLSX(QObject *parent = Q_NULLPTR);

    Q_INVOKABLE bool jsonArrayToSpreadSheet(const QJsonArray &jsonArr, const QString &name = "Untitled");

private:
};

} // namespace NaiSys

#endif // NAISYS_NAISYSXLSX_H
