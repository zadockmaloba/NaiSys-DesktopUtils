#ifndef NAISYSAPPLICATIONCONTROLLER_H
#define NAISYSAPPLICATIONCONTROLLER_H

#include <QQuickItem>
#include <QJsonArray>

class NaiSysApplicationController: public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
public:
    NaiSysApplicationController();

    Q_INVOKABLE static QJsonArray appModel();
    Q_INVOKABLE static void setAppModel(const QJsonArray &newAppModel);

signals:

private://static members
    static QJsonArray m_appModel;

};

#endif // NAISYSAPPLICATIONCONTROLLER_H
