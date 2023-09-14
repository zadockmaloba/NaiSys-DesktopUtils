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
};

#endif // NAISYSNETWORKWRAPPER_H
