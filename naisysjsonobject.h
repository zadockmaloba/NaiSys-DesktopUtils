#ifndef NAISYSJSONOBJECT_H
#define NAISYSJSONOBJECT_H

#include "NaiSys_DesktopUtils_global.h"

#include <QObject>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QSqlQueryModel>
#include <QSql>
#include <QSqlRecord>
#include <QDebug>
#include <QJsonDocument>

class NAISYSDESKTOPUTILS_EXPORT NaiSysJsonObject : public QObject
{
    Q_OBJECT
public:
    explicit NaiSysJsonObject(QObject *parent = nullptr);

signals:

public:
    static const QByteArray qryModelToJson(const QSqlQueryModel* mdl);
    static QStringList jsonDocToStringArr(const QByteArray& _data);
    static const QStringList jsonValsToStringList(const QJsonObject &obj);
    static const QString jsonValsToHtmlTable(const QJsonArray &jarr);

private:
    QJsonObject *m_jobj;
};

#endif // NAISYSJSONOBJECT_H
