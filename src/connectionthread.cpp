#include "connectionthread.h"
#include "QtGlobal"

#include "naisyshttpparser.h"
#include "naisyshttpresponse.h"
#include "streamio.h"

namespace NaiSys {
ConnectionThread::ConnectionThread(const qintptr descriptor, ServerObject *parent)
    : ServerObject{parent},
      m_descriptor{descriptor},
      m_expectingBody{0}
{
}

int ConnectionThread::listenPort() const
{return m_listenPort;}

void ConnectionThread::setListenPort(int newListenPort)
{m_listenPort = newListenPort;}

const QString &ConnectionThread::listenAddress() const
{return m_listenAddress;}

void ConnectionThread::setListenAddress(const QString &newListenAddress)
{m_listenAddress = newListenAddress;}

void ConnectionThread::run()
{
    auto m_tcpSocket = new QTcpSocket();

    if(!m_tcpSocket->setSocketDescriptor(m_descriptor)){
        StreamIO::println("[SOCKET_CREATE_FAIL]: %arg",
                          QSTRING_TO_CSTR(m_tcpSocket->errorString()));
        return;
    }
    else StreamIO::println("Socket created on new Thread : %arg",
                           QSTRING_TO_CSTR(this->currentThread()->objectName()));

    //QObject::connect(&m_tcpSocket, &QTcpSocket::connected, this, &ConnectionThread::onConnected);
    QObject::connect(m_tcpSocket, &QTcpSocket::connected, [](){
        StreamIO::println("Connection Established.");
    });

    //QObject::connect(&m_tcpSocket, &QIODevice::readyRead, this, &ConnectionThread::onReadyRead);
    QObject::connect(m_tcpSocket, &QIODevice::readyRead, [m_tcpSocket, this](){
        QByteArray _headerBA;

        //read header
        bool EOH = false;
        while (m_tcpSocket->canReadLine() && !EOH && !m_expectingBody) {
            auto const rd = m_tcpSocket->readLine();

            EOH = (rd == "\r\n");

            EOH ? _headerBA : _headerBA.append(rd);
        }
        _headerBA.chop(2); //has no effect when expecting body

        auto const bodyBytes = m_tcpSocket->bytesAvailable();

        StreamIO::println("{{SOCKET}} :: Available bytes: %arg",
                          QSTRING_TO_CSTR(QString::number(bodyBytes)));
        StreamIO::println("{{HEADER_READ}} :: %arg",
                          QSTRING_TO_CSTR(_headerBA));

        auto bodyBytesRead = m_tcpSocket->read(bodyBytes);
        StreamIO::println("{{BODY_BYTES_READ}} :: %arg",
                          QSTRING_TO_CSTR(QString::number(bodyBytesRead.size())));

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

        qDebug() << "////___ BYTES COLLECTED: "
                 << (qsizetype)parser.desirialized()._body.size();
        qDebug() << "////___ BYTES MISSING: "<< _size;

        if(_size > 0){
            this->m_expectingBody = true;
            qDebug() << "{{AWAITING SOME DATA}}: " << _size;
            m_bufferRequest = reqst;
            m_tcpSocket->flush();

            return;
        }

        m_tcpSocket->flush();
        auto resp = parser.renderHttp();
        m_tcpSocket->write(resp.toByteArray());

        if(!parser.keepAlive())
        {
            StreamIO::println("Attempting disconnect");
            //m_tcpSocket->close();
        }
    });

    //QObject::connect(&m_tcpSocket, &QTcpSocket::disconnected, this, &ConnectionThread::onDisconnected);
    QObject::connect(m_tcpSocket, &QTcpSocket::disconnected, [m_tcpSocket, this](){
        m_tcpSocket->close();
        m_tcpSocket->deleteLater();
        StreamIO::println("Socket Closed Successfully");
        this->exit(0);
    });

#if QT_VERSION > QT_VERSION_CHECK(5, 15, 0)
    QObject::connect(m_tcpSocket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)), this, SLOT(onErrorOccurred(QAbstractSocket::SocketError)));
#else
    QObject::connect(m_tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onErrorOccurred(QAbstractSocket::SocketError)));
#endif

    exec();
}

void ConnectionThread::onAboutToClose()
{

}

void ConnectionThread::onBytesWritten(qint64 bytes)
{
    StreamIO::println("Bytes: %arg", QSTRING_TO_CSTR(QString::number(bytes)));
}

void ConnectionThread::onChannelBytesWritten(int channel, qint64 bytes)
{
    StreamIO::println("Channel: %arg Bytes: %arg",
                      QSTRING_TO_CSTR(QString::number(channel)),
                      QSTRING_TO_CSTR(QString::number(bytes)));
}

void ConnectionThread::onChannelReadyRead(int channel)
{
    StreamIO::println("Channel: %arg",
                      QSTRING_TO_CSTR(QString::number(channel)));
}

void ConnectionThread::onReadChannelFinished()
{

}

void ConnectionThread::onErrorOccurred(QAbstractSocket::SocketError socketError)
{
    auto const _b = qobject_cast<QTcpSocket*> (sender());
    StreamIO::println("ERROR: %arg PORT %arg",
                      QSTRING_TO_CSTR(_b->errorString()),
                      QSTRING_TO_CSTR(QString::number(_b->localPort())));
    qDebug() << socketError;
}

void ConnectionThread::onHostFound()
{

}

void ConnectionThread::
onProxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator)
{
    qDebug()<< "PROXY AUTH() REQUIRED: " << proxy << authenticator;
}

void ConnectionThread::onStateChanged(QAbstractSocket::SocketState socketState)
{
    qDebug() << "Socket State: " << socketState;
}
}
