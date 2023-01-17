#include "naisyshttpserver.h"
#include "connectionthread.h"
#include "streamio.h"

namespace NaiSys {
NaiSysHttpServer::NaiSysHttpServer(QObject *parent)
    : QTcpServer{parent}
{

}

NaiSysHttpServer::NaiSysHttpServer(const ServerAddress &lAddr, QObject *parent)
    : QTcpServer{parent},
      m_listenPort{lAddr._listen_port},
      m_listenAddress{lAddr._listen_address}
{

}

bool NaiSysHttpServer::startServer()
{
    if(!this->listen(QHostAddress(m_serverParams.Address), m_serverParams.Port)){
        StreamIO::println(nErrorLog"Server Failed To Start.");
        return false;
    }
    else {
        StreamIO::println(nMsgLog"Server Started Succesfully");
        StreamIO::println(nMsgLog"Listening on [Addr]: %arg [Port]: %arg",
                          QSTRING_TO_CSTR(m_serverParams.Address),
                          QSTRING_TO_CSTR(QString::number(m_serverParams.Port)));
    }
    return true;
}

void NaiSysHttpServer::incomingConnection(qintptr socketDescriptor)
{
    if(serverParams().Ssl){
        StreamIO::println(nMsgLog"Opening SSL socket");
        auto workerThread = new ConnectionThread(socketDescriptor);
        workerThread->setServerParams(m_serverParams);
        workerThread->setListenPort(m_listenPort);
        workerThread->setListenAddress(m_listenAddress);

        QObject::connect(workerThread, SIGNAL(finished()), workerThread,SLOT(deleteLater()), Qt::DirectConnection);
        workerThread->start();
    }
    else{
        StreamIO::println(nMsgLog"Opening socket");
        auto workerThread = new ConnectionThread(socketDescriptor);
        workerThread->setServerParams(m_serverParams);
        workerThread->setListenPort(m_listenPort);
        workerThread->setListenAddress(m_listenAddress);
        QObject::connect(workerThread, SIGNAL(finished()), workerThread,SLOT(deleteLater()), Qt::DirectConnection);
        workerThread->start();
    }
}

const server_params &NaiSysHttpServer::serverParams() const
{return m_serverParams;}

void NaiSysHttpServer::setServerParams(const server_params &newServerParams)
{m_serverParams = newServerParams;}

int NaiSysHttpServer::listenPort() const
{return m_listenPort;}

void NaiSysHttpServer::setListenPort(int newListenPort)
{m_listenPort = newListenPort;}

const QString &NaiSysHttpServer::listenAddress() const
{return m_listenAddress;}

void NaiSysHttpServer::setListenAddress(const QString &newListenAddress)
{m_listenAddress = newListenAddress;}

}
