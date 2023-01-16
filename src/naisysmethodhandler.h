#ifndef NAISYS_NAISYSMETHODHANDLER_H
#define NAISYS_NAISYSMETHODHANDLER_H

#include <QObject>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QString>

#include "systemconfig.h"
#include "naisysdefs.h"
#include "naisyshttpresponse.h"

#include "serverobject.h"


#include <QDateTime>

namespace NaiSys {

class MethodHandler : public ServerObject
{
private:
    struct UrlParams{
        QString url_destination;
        QStringList url_keys;
        QJsonObject url_dict;
    };

public:
    MethodHandler();
    MethodHandler(const DesirializedData &data, ServerObject *parent);
    const NaiSysHttpResponse get();

    const DesirializedData &desirialized() const;
    void setDesirialized(const DesirializedData &newDesirialized);

    const NaiSysHttpResponse &defaultResponse() const;

private://methods
    const QStringList messageParser(const QString &rawMsg);
    const QString *querryParser(const QString &rawMsg);
    void post_binrary_image(const DesirializedData &data);
    QByteArray get_binary_image(const DesirializedData &data);
    void parseUrlParameters();

private:
    DesirializedData m_desirialized;
    UrlParams m_parameters;
    const NaiSysHttpResponse m_defaultResponse {"HTTP/1.1 200 Ok\r\n", "{Message Received}"};
    QMap <QString, QString> m_routingTable = {
        {"/", SystemConfig::readConfigFile().value("Landing-Page").toString()},
        {"index", SystemConfig::readConfigFile().value("Landing-Page").toString()},
        {"/favicon.ico", SystemConfig::readConfigFile().value("Landing-Page").toString()}
    };
};

} // namespace NaiSys

#endif // NAISYS_NAISYSMETHODHANDLER_H
