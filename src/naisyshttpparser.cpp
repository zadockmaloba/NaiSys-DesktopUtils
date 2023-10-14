#include "naisyshttpparser.h"
#include "naisysmethodhandler.h"
#include "streamio.h"

namespace NaiSys {

HttpParser::HttpParser(ServerObject *parent)
    : ServerObject{parent}
{
    if(parent != nullptr)
        setServerParams(parent->serverParams());
}

HttpParser::HttpParser(const NaiSysHttpRequest &request, ServerObject *parent)
    : ServerObject{parent}
{
    if(parent != nullptr)
        setServerParams(parent->serverParams());
    this->m_desirialized = { HttpParser::getJsonHeader(request.header()),
                             request.body(),
                             request.header()
                           };
    this->m_keepAlive = m_desirialized._header.value("Connection")
            .toString().contains("keep-alive", Qt::CaseInsensitive);
}

HttpParser::HttpParser(const NaiSysHttpResponse &response, ServerObject *parent)
    : ServerObject{parent}
{
    this->m_desirialized = { HttpParser::getJsonHeader(response.header()),
                             response.body(),
                             response.header()
                           };
}

const NaiSysHttpResponse HttpParser::renderHttp()
{
    StreamIO::println("[HTTP_PARSER_MSG]: RENDERING METHOD");
    return NaiSys::MethodHandler(m_desirialized, this).get();
}

const NaiSysHttpResponse HttpParser::getDefaultResponse()
{
    return NaiSys::MethodHandler().defaultResponse();
}

DesirializedData &HttpParser::desirialized()
{return m_desirialized;}

void HttpParser::setDesirialized(const DesirializedData &newDesirialized)
{m_desirialized = newDesirialized;}

const DesirializedData HttpParser::getDesirializedData([[maybe_unused]]QByteArray &data)
{
    return DesirializedData(); //TODO: implement
}

const QJsonObject HttpParser::getJsonHeader(const QByteArray &header)
{
    QJsonObject jsObj;
    auto const _b = QString::fromUtf8(QByteArray::fromPercentEncoding(header)).split("\r\n");
    auto const _d = _b[0].split(" ");
    if(_d.size() >= 3){
        jsObj = {{"Method", _d[0]},
                 {"Path", _d[1]},
                 {"Protocol", _d[2]}};

        for(int i=0; i<_b.size()-1; ++i){
            auto const _c = _b[i+1].split(":");
            jsObj.insert(_c[0], QJsonValue(_c[1]));
        }
    }
    return jsObj;
}

bool HttpParser::keepAlive() const
{
    return m_keepAlive;
}

} // namespace NaiSys
