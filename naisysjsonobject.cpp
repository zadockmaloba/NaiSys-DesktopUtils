#include "naisysjsonobject.h"
#include "naisysdocumenthandler.h"

NaiSysJsonObject::NaiSysJsonObject(QObject *parent) :
    QObject(parent),
    m_jobj(new QJsonObject)
{

}

const QByteArray NaiSysJsonObject::qryModelToJson(const QSqlQueryModel *mdl)
{
    QJsonObject mObj; QJsonArray jArr; QString header;

    for(int i=0; i < mdl->rowCount(); i++){
        for(int j=0; j < mdl->columnCount(); j++){
            header = mdl->headerData(j, Qt::Horizontal).toString();
            auto xval = mdl->record(i).value(j).toString();
            mObj.insert(header, QJsonValue(xval));
        }
        jArr.append(mObj);
    }

    QJsonDocument doc(jArr);
    auto retVal = doc.toJson(QJsonDocument::Compact);

    qDebug() <<"[RESPONSE_SIZE] "<< retVal.size();
    return retVal;
}

QStringList NaiSysJsonObject::jsonDocToStringArr(const QByteArray &_data)
{
    QJsonParseError jErr; QStringList _ret;
    const auto var1 = QJsonDocument::fromJson(_data, &jErr).toVariant().toMap().values();
    qDebug() <<"[jsonDocToStringArr(const QByteArray &_data)] "<<jErr.errorString();
    qDebug() <<"VALUE_ARRAY_SIZE: "<<var1.size();
    for(auto &v : var1) _ret.append(v.toString());
    return _ret;
}

const QStringList NaiSysJsonObject::jsonValsToStringList(const QJsonObject &obj)
{
    auto ret = QStringList();
    auto const v = obj.toVariantMap().values();
    for (auto &a : v) ret.append(a.toString());
    return ret;
}

const QString NaiSysJsonObject::jsonValsToHtmlTable(const QJsonArray &jarr)
{
    auto ret = QString("<table>");
    auto header = jarr.at(0).toObject().keys();

    // Table Headers
    ret.append("<tr>");
    for (auto const &v : header) ret.append("<th>"+v.toUpper()+"</th>");
    ret.append("</tr>");

    // Table Body
    for(auto &obj : jarr){
        auto vals = NaiSysJsonObject::jsonValsToStringList(obj.toObject());
        ret.append("<tr>");
        for(auto const &v : vals) ret.append("<td>"+v+"</td>");
        ret.append("</tr>");
    }
    ret.append("</table>");
    return ret;
}
