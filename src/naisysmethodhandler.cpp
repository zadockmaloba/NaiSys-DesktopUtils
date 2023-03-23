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

    ServerLang::parser prs(serverParams().Entry_Script,
                           serverParams().Site_Dir);
    prs.READ();
    NaiSys::ServerLang::RunTime rt(*prs.globalAST());
//    rt.injectRTDeclarations({
//                                {"RUNTIME_URL_PARAMS", QString(QJsonDocument(m_parameters.url_dict).toJson())},
//                                {"RUNTIME_HTTP_HEADERS", QString(QJsonDocument(m_desirialized._header).toJson())},
//                                {"RUNTIME_HTTP_BODY", QString(m_desirialized._body)}
//                            });
    rt.start();

//    StreamIO::println("[[GET]]: %arg", QSTRING_TO_CSTR(l));
//    QVariantMap resp;
//    if(rt.hookMap().contains(l)){
//        resp = rt.hookMap().value(l)();
//        //qDebug() << "HOOK_RESPONSE: " << resp << " : " << resp.value("content_type").toMap().value("value").toString();
//        NaiSysHttpResponse postResp("HTTP/1.1 200 Ok\r\n", resp.value("body").toMap().value("value").toByteArray());//TODO: Find a better method
//        //postResp.appendRawHeader("Connection", "keep-alive");
//        postResp.appendDefinedHeader(DefinedHeaders::ContentType, resp.value("content_type").toMap().value("value").toByteArray().replace('\"',""));
//        postResp.appendDefinedHeader(DefinedHeaders::ContentLength, QString::number(postResp.body().size()).toUtf8());

//        return postResp;
//    }
//    else if(rt.hookMap().contains("/*")){
//        StreamIO::println("[ROUTER]: Fetching default route");
//        resp = rt.hookMap().value("/*")();
//        NaiSysHttpResponse postResp("HTTP/1.1 200 Ok\r\n", resp.value("body").toMap().value("value").toByteArray());//TODO: Find a better method
//        //postResp.appendRawHeader("Connection", "keep-alive");
//        postResp.appendDefinedHeader(DefinedHeaders::ContentType, resp.value("content_type").toMap().value("value").toByteArray().replace('\"',""));
//        postResp.appendDefinedHeader(DefinedHeaders::ContentLength, QString::number(postResp.body().size()).toUtf8());

//        return postResp;
//    }
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
