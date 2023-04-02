#include "naisysmethodhandler.h"
#include "serverlangparser.h"
#include "serverlangruntime.h"

#include "servercalls.h"
#include "streamio.h"

namespace NaiSys {

MethodHandler::MethodHandler()
{

}

MethodHandler::MethodHandler(const DesirializedData &data, ServerObject *parent)
    : ServerObject{parent},
      m_desirialized{data}
{
    if(parent != nullptr)
        setServerParams(parent->serverParams());
}

const NaiSysHttpResponse MethodHandler::get()
{
    qDebug() << "GET REQUEST";
    this->parseUrlParameters();

    auto const l = m_parameters.url_destination;
    StreamIO::println("[[GET]]: %arg", QSTRING_TO_CSTR(l));

    ServerLang::Parser prs(serverParams().Entry_Script,
                           serverParams().Site_Dir);
    prs.READ();

    NaiSys::ServerLang::RunTime rt(prs.globalAST());

    ServerLang::String http_body(m_desirialized._body);
    http_body.setName("RUNTIME_HTTP_BODY");
    http_body.setValue(std::make_shared<QVariant>(m_desirialized._body));

    ServerLang::Struct http_params;
    http_params.setName("RUNTIME_HTTP_PARAMS");
    http_params.setValue(std::make_shared<QVariant>(m_parameters.url_dict));

    ServerLang::Struct http_headers;
    http_headers.setName("RUNTIME_HTTP_HEADERS");
    http_headers.setValue(std::make_shared<QVariant>(m_desirialized._header));

    rt.injectRTDeclarations({
        std::make_shared<ServerLang::STNode>(http_body),
        std::make_shared<ServerLang::STNode>(http_params),
        std::make_shared<ServerLang::STNode>(http_headers)
    });

    rt.start();

    if(rt.BufferAST()->declarationMap().has(l)) {
        qDebug() << "[ROUTER]: Path found";
        auto sc = rt.BufferAST()->declarationMap().at(l);
        rt.interprate(sc);
        auto const _hdr = sc->declarationMap().at("Header");
        auto const _bdy = sc->declarationMap().at("Body");

        //qDebug() << "Content-Type: " << _hdr->value();
        //qDebug() << "Body: " << _bdy->value();

        NaiSysHttpResponse postResp("HTTP/1.1 200 Ok\r\n", _bdy->value()->toByteArray());
        //postResp.appendRawHeader("Connection", "keep-alive");
        postResp.appendDefinedHeader(DefinedHeaders::ContentType,
                                     _hdr->value()->toByteArray());
        postResp.appendDefinedHeader(DefinedHeaders::ContentLength,
                                     QByteArray::number(postResp.body().size()));

        return postResp;
    }
    else if(rt.BufferAST()->declarationMap().has("/*")) {
        qDebug() << "[ROUTER]: Default path found";
        auto sc = rt.BufferAST()->declarationMap().at("/*");
        rt.interprate(sc);
        auto const _hdr = sc->declarationMap().at("Header");
        auto const _bdy = sc->declarationMap().at("Body");

        //qDebug() << "Content-Type: " << _hdr->value();
        //qDebug() << "Body: " << _bdy->value();

        NaiSysHttpResponse postResp("HTTP/1.1 200 Ok\r\n", _bdy->value()->toByteArray());
        //postResp.appendRawHeader("Connection", "keep-alive");
        postResp.appendDefinedHeader(DefinedHeaders::ContentType,
                                     _hdr->value()->toByteArray());
        postResp.appendDefinedHeader(DefinedHeaders::ContentLength,
                                     QByteArray::number(postResp.body().size()));

        return postResp;
    }

    return NaiSysHttpResponse("HTTP/1.1 400 Bad\r\n", "");
}

const DesirializedData &MethodHandler::desirialized() const
{return m_desirialized;}

void MethodHandler::setDesirialized(const DesirializedData &newDesirializedData)
{m_desirialized = newDesirializedData;}

const NaiSysHttpResponse &MethodHandler::defaultResponse() const
{return m_defaultResponse;}

const QStringList MethodHandler::messageParser(const QString &rawMsg)
{
    return rawMsg.split("::/");
}

const QString *MethodHandler::querryParser(const QString &rawMsg)
{
    auto const varr = messageParser(rawMsg); //return the separated string as an array
    auto const x = new QString(callsArr[varr[0]]);

    if(varr.size() == 2) return &x->replace("_?1",varr[1]);

    else if(varr.size() > 2){
        const int eval = x->count("_?");
        for (int i = 1; i <= eval; ++i)
            x->replace("_?"+QString::number(i), varr[i]);
        return x;
    }
    else return x;
}

void MethodHandler::parseUrlParameters()
{
    auto const route = m_desirialized._header.value("Path").toString();
    QStringList params;
    route.contains("?") ? params = route.split("?") : params = QStringList{route};
    m_parameters.url_destination = params[0];
    if(params.size() == 2){
        auto const dicts = params[1].split("&");
        for(auto &v : dicts){
            auto tmp = v.split("=");
            m_parameters.url_keys.append(tmp[0]);
            if(tmp.size() == 2) m_parameters.url_dict.insert(tmp[0], tmp[1]);
        }
    }
    qDebug() << m_parameters.url_dict;
}

} // namespace NaiSys
