#include "networkapi.h"
#include <QCoreApplication>

NetworkController::NetworkController(QObject *parent)
    : QObject{parent}
{

}

QNetworkAccessManager* NetworkController::netManager()
{
    return m_netManager.get();
}

const NetworkController::job_map &NetworkController::requestHeap()
{
    return m_requestHeap;
}

void NetworkController::createPushRequest(const QString& path, const QByteArray &data)
{

}

QByteArray NetworkController::createPushRequestAwait(const QString& path, const QByteArray &data)
{

}

void NetworkController::createGetRequest(const QString& path, const QByteArray &data)
{
    auto reply = netManager()->get(QNetworkRequest("http://"+m_serverHost+":"+QString::number(m_serverPort)+path));

    connect(reply, &QNetworkReply::finished, [reply]() {
        qDebug() << reply->readAll();
    });
}

QByteArray NetworkController::createGetRequestAwait(const QString& path, const QByteArray &data)
{
    QByteArray ret;

    auto reply = netManager()->get(
        QNetworkRequest("http://" + m_serverHost + ":" + QString::number(m_serverPort) + path));

    connect(reply, &QNetworkReply::finished, [reply, &ret]() { ret = reply->readAll(); });

    connect(reply, &QNetworkReply::errorOccurred, [&]() {
        auto tmp = reply->errorString();
        qDebug() << tmp;
        // emit requestError(tmp);
    });

    reply->waitForReadyRead(3000);

    while(!reply->isFinished()) {
        QCoreApplication::processEvents();
    }

    qDebug() << "Got response";

    return ret;
}

void NetworkController::createPostRequest(const QString &path,
                                          const QByteArray &data,
                                          const QByteArray &type)
{
    QNetworkRequest req("http://" + m_serverHost + ":" + QString::number(m_serverPort) + path);
    req.setHeader(QNetworkRequest::ContentTypeHeader, type);
    req.setHeader(QNetworkRequest::ContentLengthHeader, data.length());

    auto reply = netManager()->post(req, data);

    connect(reply, &QNetworkReply::finished, [reply]() { qDebug() << reply->readAll(); });
}

QByteArray NetworkController::createPostRequestAwait(const QString &path,
                                                     const QByteArray &data,
                                                     const QByteArray &type)
{
    QByteArray ret;

    QNetworkRequest req("http://" + m_serverHost + ":" + QString::number(m_serverPort) + path);
    req.setHeader(QNetworkRequest::ContentTypeHeader, type);
    req.setHeader(QNetworkRequest::ContentLengthHeader, data.length());

    auto reply = netManager()->post(req, data);

    connect(reply, &QNetworkReply::finished, [reply, &ret]() { ret = reply->readAll(); });

    connect(reply, &QNetworkReply::errorOccurred, [reply]() { qDebug() << reply->errorString(); });

    reply->waitForReadyRead(3000);

    while (!reply->isFinished()) {
        QCoreApplication::processEvents();
    }

    qDebug() << "Got response";

    return ret;
}

void NetworkController::createPushRequestSecure(const QString &path, const QByteArray &data)
{
    
}

QByteArray NetworkController::createPushRequestAwaitSecure(const QString &path, const QByteArray &data)
{

}

void NetworkController::createGetRequestSecure(const QString &path, const QByteArray &data)
{
    auto reply = netManager()->get(QNetworkRequest("https://"+m_serverHost+":"+QString::number(m_serverPort)+path));

    connect(reply, &QNetworkReply::finished, [reply]() {
        qDebug() << reply->readAll();
    });
}

QByteArray NetworkController::createGetRequestAwaitSecure(const QString &path, const QByteArray &data)
{
    QByteArray ret;

    auto reply = netManager()->get(
        QNetworkRequest("https://" + m_serverHost + ":" + QString::number(m_serverPort) + path));

    connect(reply, &QNetworkReply::finished, [reply, &ret]() { ret = reply->readAll(); });

    connect(reply, &QNetworkReply::errorOccurred, [&]() { qDebug() << reply->errorString(); });

    reply->waitForReadyRead(3000);

    while(!reply->isFinished()) {
        QCoreApplication::processEvents();
    }

    qDebug() << "Got response";

    return ret;
}

void NetworkController::onRequestComplete()
{
    qDebug() << "Request complete";
}

int NetworkController::serverPort()
{
    return m_serverPort;
}

void NetworkController::setServerPort(int newServerPort)
{
    m_serverPort = newServerPort;
}

QString NetworkController::serverHost()
{
    return m_serverHost;
}

void NetworkController::setServerHost(const QString &newServerHost)
{
    m_serverHost = newServerHost;
}
