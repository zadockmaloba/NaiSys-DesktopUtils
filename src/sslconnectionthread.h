#ifndef SSLCONNECTIONTHREAD_H
#define SSLCONNECTIONTHREAD_H

#include <QThread>
#include <QSslSocket>
#include <QObject>

#include <QAuthenticator>
#include <QNetworkProxy>
#include <QAbstractSocket>

#include "naisysdefs.h"
#include "serverobject.h"

#include "naisyshttprequest.h"


namespace NaiSys {
class sslConnectionThread : public ServerObject
{
    Q_OBJECT
public:
    explicit sslConnectionThread(const qintptr descriptor, ServerObject *parent = nullptr);
    void run();

    const SslObject &sslObject() const;
    void setSslObject(const NaiSys::SslObject &newSslObject);
    qintptr descriptor() const;
    void setDescriptor(qintptr newDescriptor);
    int listenPort() const;
    void setListenPort(int newListenPort);
    const QString &listenAddress() const;
    void setListenAddress(const QString &newListenAddress);

signals:
    void startEncryption();

private slots:
    //IODevice signals
    void onAboutToClose();
    void onBytesWritten(qint64 bytes);
    void onChannelBytesWritten(int channel, qint64 bytes);
    void onChannelReadyRead(int channel);
    void onReadChannelFinished();
    void onReadyRead();
    //AbstractSocket signals
    void onConnected();
    void onDisconnected();
    void onErrorOccurred(QAbstractSocket::SocketError socketError);
    void onHostFound();
    void onProxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator);
    void onStateChanged(QAbstractSocket::SocketState socketState);
    //QSslSocket signals
    void ready();

private:
    //QSslSocket *m_sslSocket;
    SslObject m_sslObject;
    qintptr m_descriptor;
    int m_listenPort;
    QString m_listenAddress;
    bool m_expectingBody;
    NaiSysHttpRequest m_bufferRequest;
};
}

#endif // SSLCONNECTIONTHREAD_H
