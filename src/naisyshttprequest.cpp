#include "naisyshttprequest.h"

namespace NaiSys {

NaiSysHttpRequest::NaiSysHttpRequest()
{

}

NaiSysHttpRequest::NaiSysHttpRequest(const QByteArray &data)
{
    auto const a = QString::fromUtf8(data).split("\r\n\r\n");
    StreamIO::println("[HTTP_REQUEST]: Request chunks: %arg",
                      QSTRING_TO_CSTR(QString::number(a.size())));
    if( a.size() > 1 ){
        m_header = a[0].toUtf8();
        qDebug() << "HTTPREQUEST_HEADER : " << "__@@ "<<m_header;
        m_body = a[1].toUtf8();
        //qDebug() << "HTTPREQUEST_BODY : " << "__@@ "<<m_body;
    }
}

NaiSysHttpRequest::NaiSysHttpRequest(const QByteArray &header, const QByteArray &body)
    : m_header{header},
      m_body{body}
{

}

void NaiSysHttpRequest::appendDefinedHeader(const int eHeader, const QByteArray &value)
{
    switch (eHeader) {
    case DefinedHeaders::ContentType :
        appendRawHeader("Content-Type", value);
        break;
    case DefinedHeaders::ContentLength:
        appendRawHeader("Content-Length", value);
        break;
    case DefinedHeaders::Authorization:
        appendRawHeader("Authorization", value.toBase64());
        break;
    case DefinedHeaders::Cookies:
        appendRawHeader("Cookie", value);
        break;
    }
}

void NaiSysHttpRequest::appendRawHeader(const QByteArray &key, const QByteArray &value)
{
    m_header.append(key+": "+value+"\r\n");
}

void NaiSysHttpRequest::appendToBody(const QByteArray &data)
{
    m_body.append(data);
}

const QByteArray &NaiSysHttpRequest::header() const
{return m_header;}

void NaiSysHttpRequest::setHeader(const QByteArray &newHeader)
{m_header = newHeader;}

const QByteArray &NaiSysHttpRequest::body() const
{return m_body;}

void NaiSysHttpRequest::setBody(const QByteArray &newBody)
{m_body = newBody;}

} // namespace NaiSys
