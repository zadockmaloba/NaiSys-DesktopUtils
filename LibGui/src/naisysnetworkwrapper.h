#ifndef NAISYSNETWORKWRAPPER_H
#define NAISYSNETWORKWRAPPER_H

#include <QObject>
#include <QQmlEngine>

#include "networkapi.h"

class NaiSysNetworkWrapper : public NetworkController
{
    Q_OBJECT
    QML_NAMED_ELEMENT(NetworkAPI)
    QML_SINGLETON
public:
    explicit NaiSysNetworkWrapper(QObject *parent = nullptr);

public:
    Q_INVOKABLE QObject *instance() { return global_net_ctrl; }

    Q_INVOKABLE void createPushRequest(const QString &path, const QByteArray &data)
    {
        return NetworkController::createPushRequest(path, data);
    }

    Q_INVOKABLE QByteArray createPushRequestAwait(const QString &path, const QByteArray &data)
    {
        emit requestStarted();
        auto ret = NetworkController::createPushRequestAwait(path, data);
        emit requestComplete();
        return ret;
    }

    Q_INVOKABLE void createGetRequest(const QString &path, const QByteArray &data = {})
    {
        return NetworkController::createGetRequest(path, data);
    }

    Q_INVOKABLE QByteArray createGetRequestAwait(const QString &path, const QByteArray &data = {})
    {
        emit requestStarted();
        auto ret = NetworkController::createGetRequestAwait(path, data);
        emit requestComplete();

        return ret;
    }

    Q_INVOKABLE void createPushRequestSecure(const QString &path, const QByteArray &data)
    {
        return NetworkController::createPushRequestSecure(path, data);
    }

    Q_INVOKABLE QByteArray createPushRequestAwaitSecure(const QString &path, const QByteArray &data)
    {
        emit requestStarted();
        auto ret = NetworkController::createPushRequestAwaitSecure(path, data);
        emit requestComplete();

        return ret;
    }

    Q_INVOKABLE void createGetRequestSecure(const QString &path, const QByteArray &data = {})
    {
        return NetworkController::createGetRequestSecure(path, data);
    }

    Q_INVOKABLE QByteArray createGetRequestAwaitSecure(const QString &path,
                                                       const QByteArray &data = {})
    {
        emit requestStarted();
        auto ret = NetworkController::createGetRequestAwaitSecure(path, data);
        emit requestComplete();

        return ret;
    }
};

#endif // NAISYSNETWORKWRAPPER_H
