#include "sslconnectionthread.h"
#include "QtGlobal"

#include "naisyshttpresponse.h"
#include "naisyshttpparser.h"

#include "streamio.h"

namespace NaiSys {

sslConnectionThread::sslConnectionThread(const qintptr descriptor, ServerObject *parent)
    : ServerObject{parent},
      m_descriptor{descriptor},
      m_expectingBody{0}
{

}

void sslConnectionThread::run()
{
    auto m_sslSocket = new QSslSocket();

    m_sslSocket->setLocalCertificate(serverParams().Ssl_Cert);
    m_sslSocket->setPrivateKey(serverParams().Ssl_Key);

    if(!m_sslSocket->setSocketDescriptor(m_descriptor)){
        StreamIO::println("[SOCKET_CREATE_FAIL]: %arg",
                          QSTRING_TO_CSTR(m_sslSocket->errorString()));
        return;
    }
    else StreamIO::println("Socket created on new Thread : %arg",
                           QSTRING_TO_CSTR(this->currentThread()->objectName()));

    m_sslSocket->startServerEncryption();

    //FIXME: Try using lambda functions instead of local slots
    //QObject::connect(&m_sslSocket, &QSslSocket::encrypted, this, &sslConnectionThread::ready);
    QObject::connect(m_sslSocket, &QSslSocket::encrypted, [](){
        StreamIO::println("[SOCKET_STATE]: ready.");
    });
    //QObject::connect(&m_sslSocket, &QSslSocket::connected, this, &sslConnectionThread::onConnected);
    QObject::connect(m_sslSocket, &QSslSocket::connected, [](){
        StreamIO::println("Connection Established.");
    });
    //QObject::connect(&m_sslSocket, &QIODevice::readyRead, this, &sslConnectionThread::onReadyRead);
    QObject::connect(m_sslSocket, &QIODevice::readyRead, [m_sslSocket, this](){
        QByteArray _headerBA;

        //read header
        bool EOH = false;
        while (m_sslSocket->canReadLine() && !EOH && !m_expectingBody) {
            auto const rd = m_sslSocket->readLine();

            EOH = (rd == "\r\n");

            EOH ? _headerBA : _headerBA.append(rd);
        }
        _headerBA.chop(2); //has no effect when expecting body

        auto const bodyBytes = m_sslSocket->bytesAvailable();

        StreamIO::println("{{SOCKET}} :: Available bytes: %arg", QSTRING_TO_CSTR(QString::number(bodyBytes)));
        StreamIO::println("{{HEADER_READ}} :: %arg", QSTRING_TO_CSTR(_headerBA));

        auto bodyBytesRead = m_sslSocket->read(bodyBytes);
        StreamIO::println("{{BODY_BYTES_READ}} :: %arg", QSTRING_TO_CSTR(QString::number(bodyBytesRead.size())));

        auto const _b = bodyBytesRead;

        StreamIO::println("{{BODY_READ}} :: %arg", QSTRING_TO_CSTR(_b));

        auto reqst = NaiSysHttpRequest();
        reqst.setHeader(_headerBA);
        reqst.setBody(_b);

        if(m_expectingBody){
            reqst = m_bufferRequest;
            reqst.appendToBody(_b);
            m_expectingBody = false;
        }

        StreamIO::println("Instantiate parser");
        auto parser = HttpParser(reqst);
        parser.setServerParams(this->serverParams());

        auto const _size = (qsizetype)parser.desirialized()
                ._header.value("Content-Length")
                .toString().toInt()
                - (qsizetype)parser.desirialized()._body.size();

        qDebug() << "////___ BYTES COLLECTED: "<< (qsizetype)parser.desirialized()._body.size();
        qDebug() << "////___ BYTES MISSING: "<< _size;

        if(_size > 0){
            this->m_expectingBody = true;
            qDebug() << "{{AWAITING SOME DATA}}: " << _size;
            m_bufferRequest = reqst;
            m_sslSocket->flush();

            return;
        }

        m_sslSocket->flush();
        auto resp = parser.renderHttp();
        m_sslSocket->write(resp.toByteArray());

        if(!parser.keepAlive())
        {
            StreamIO::println("Attempting disconnect");
        }
    });
    //QObject::connect(&m_sslSocket, &QSslSocket::disconnected, this, &sslConnectionThread::onDisconnected);
    QObject::connect(m_sslSocket, &QSslSocket::disconnected,[m_sslSocket, this](){
        m_sslSocket->close();
        StreamIO::println("Socket Closed Successfully");
        m_sslSocket->deleteLater();
        this->exit(0);
    });
#if QT_VERSION > QT_VERSION_CHECK(5, 15, 0)
    QObject::connect(m_sslSocket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)),
                     this, SLOT(onErrorOccurred(QAbstractSocket::SocketError)));
#else
    QObject::connect(m_sslSocket, SIGNAL(error(QAbstractSocket::SocketError)),
                     this, SLOT(onErrorOccurred(QAbstractSocket::SocketError)));
#endif

    exec();
}

const NaiSys::SslObject &sslConnectionThread::sslObject() const
{return m_sslObject;}

void sslConnectionThread::setSslObject(const NaiSys::SslObject &newSslObject)
{m_sslObject = newSslObject;}

qintptr sslConnectionThread::descriptor() const
{return m_descriptor;}

void sslConnectionThread::setDescriptor(qintptr newDescriptor)
{m_descriptor = newDescriptor;}

int sslConnectionThread::listenPort() const
{return m_listenPort;}

void sslConnectionThread::setListenPort(int newListenPort)
{m_listenPort = newListenPort;}

const QString &sslConnectionThread::listenAddress() const
{return m_listenAddress;}

void sslConnectionThread::setListenAddress(const QString &newListenAddress)
{m_listenAddress = newListenAddress;}


void sslConnectionThread::onAboutToClose()
{
    qDebug() << "[sslSOCKET]: Closing socket....";
}

void sslConnectionThread::onBytesWritten(qint64 bytes)
{
    StreamIO::println("Bytes: %arg", QSTRING_TO_CSTR(QString::number(bytes)));
}

void sslConnectionThread::onChannelBytesWritten(int channel, qint64 bytes)
{
    StreamIO::println("Channel: %arg Bytes: %arg",
                      QSTRING_TO_CSTR(QString::number(channel)),
                      QSTRING_TO_CSTR(QString::number(bytes)));
}

void sslConnectionThread::onChannelReadyRead(int channel)
{
    StreamIO::println("Channel: %arg",
                      QSTRING_TO_CSTR(QString::number(channel)));
}

void sslConnectionThread::onReadChannelFinished()
{
    qDebug() << "[CHANNEL]: Read Channel finnished";
}

void sslConnectionThread::onReadyRead()
{
    auto const m_sslSocket = qobject_cast<QSslSocket*> (sender());
    QByteArray _headerBA;

    //read header
    bool EOH = false;
    while (m_sslSocket->canReadLine() && !EOH && !m_expectingBody) {
        auto const rd = m_sslSocket->readLine();

        EOH = (rd == "\r\n");

        EOH ? _headerBA : _headerBA.append(rd);
    }
    _headerBA.chop(2); //has no effect when expecting body

    auto const bodyBytes = m_sslSocket->bytesAvailable();

    StreamIO::println("{{SOCKET}} :: Available bytes: %arg", QSTRING_TO_CSTR(QString::number(bodyBytes)));
    StreamIO::println("{{HEADER_READ}} :: %arg", QSTRING_TO_CSTR(_headerBA));

    auto bodyBytesRead = m_sslSocket->read(bodyBytes);
    StreamIO::println("{{BODY_BYTES_READ}} :: %arg", QSTRING_TO_CSTR(QString::number(bodyBytesRead.size())));

    auto const _b = bodyBytesRead;

    StreamIO::println("{{BODY_READ}} :: %arg", QSTRING_TO_CSTR(_b));

    auto reqst = NaiSysHttpRequest();
    reqst.setHeader(_headerBA);
    reqst.setBody(_b);

    if(m_expectingBody){
        reqst = m_bufferRequest;
        reqst.appendToBody(_b);
        m_expectingBody = false;
    }

    StreamIO::println("Instantiate parser");
    auto parser = HttpParser(reqst);

    auto const _size = (qsizetype)parser.desirialized()
            ._header.value("Content-Length")
            .toString().toInt()
            - (qsizetype)parser.desirialized()._body.size();

    qDebug() << "////___ BYTES COLLECTED: "<< (qsizetype)parser.desirialized()._body.size();
    qDebug() << "////___ BYTES MISSING: "<< _size;

    if(_size > 0){
        this->m_expectingBody = true;
        qDebug() << "{{AWAITING SOME DATA}}: " << _size;
        m_bufferRequest = reqst;
        m_sslSocket->flush();

        return;
    }

    m_sslSocket->flush();
    auto resp = parser.renderHttp();
    m_sslSocket->write(resp.toByteArray());

    if(!parser.keepAlive())
    {
        StreamIO::println("Attempting disconnect");
    }
}

void sslConnectionThread::onConnected()
{
    StreamIO::println("Connection Established.");
}

void sslConnectionThread::onDisconnected()
{
    auto const m_sslSocket = qobject_cast<QSslSocket*> (sender());
    m_sslSocket->close();
    StreamIO::println("Socket Closed Successfully");
    this->exit(0);
}

void sslConnectionThread::onErrorOccurred(QAbstractSocket::SocketError socketError)
{
    auto const _b = qobject_cast<QSslSocket*> (sender());
    StreamIO::println("ERROR: %arg PORT %arg",
                      QSTRING_TO_CSTR(_b->errorString()),
                      QSTRING_TO_CSTR(QString::number(_b->localPort())));
    qDebug() << socketError;
}

void sslConnectionThread::onHostFound()
{

}

void sslConnectionThread::onProxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator)
{
    qDebug()<< "PROXY AUTH() REQUIRED: " << proxy << authenticator;
}

void sslConnectionThread::onStateChanged(QAbstractSocket::SocketState socketState)
{
    qDebug() << "Socket State: " << socketState;
}

void sslConnectionThread::ready()
{
    qDebug() << "Ready";
}

}
