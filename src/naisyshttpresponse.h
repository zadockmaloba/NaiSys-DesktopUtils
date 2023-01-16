#ifndef NaiSysHttpResponse_H
#define NaiSysHttpResponse_H

#include <QObject>
#include "naisysdefs.h"

namespace NaiSys {

class NaiSysHttpResponse
{
public:
    NaiSysHttpResponse();
    explicit NaiSysHttpResponse(const QByteArray &data);
    NaiSysHttpResponse(const QByteArray &header, const QByteArray &body);

    void appendDefinedHeader(const int eHeader, const QByteArray &value);
    void appendRawHeader(const QByteArray &key, const QByteArray &value);

    const QByteArray toByteArray();

    const QByteArray &header() const;
    void setHeader(const QByteArray &newHeader);
    const QByteArray &body() const;
    void setBody(const QByteArray &newBody);

private:
    QByteArray m_header, m_body;
};

}

#endif // NaiSysHttpResponse_H
