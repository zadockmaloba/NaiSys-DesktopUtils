#ifndef CONNECTIONTHREAD_H
#define CONNECTIONTHREAD_H

#include <QThread>
#include <QObject>
#include <QTcpSocket>

#include <QNetworkProxy>
#include <QAuthenticator>
#include <QAbstractSocket>

#include "naisyshttprequest.h"
#include "serverobject.h"


namespace NaiSys {
class ConnectionThread : public ServerObject
{
    Q_OBJECT
public:
    explicit ConnectionThread(const qintptr descriptor, ServerObject *parent = nullptr);
    void run();

    int listenPort() const;
    void setListenPort(int newListenPort);
    const QString &listenAddress() const;
    void setListenAddress(const QString &newListenAddress);

private slots:
    //IODevice signals
    void onAboutToClose();
    void onBytesWritten(qint64 bytes);
    void onChannelBytesWritten(int channel, qint64 bytes);
    void onChannelReadyRead(int channel);
    void onReadChannelFinished();
    void onErrorOccurred(QAbstractSocket::SocketError socketError);
    void onHostFound();
    void onProxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator);
    void onStateChanged(QAbstractSocket::SocketState socketState);

private:
    qintptr m_descriptor;
    int m_listenPort;
    QString m_listenAddress;
    bool m_expectingBody;
    NaiSysHttpRequest m_bufferRequest;
};
}

#endif // CONNECTIONTHREAD_H
