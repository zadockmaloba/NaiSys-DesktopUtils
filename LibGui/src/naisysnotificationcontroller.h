#ifndef NAISYSNOTIFICATIONCONTROLLER_H
#define NAISYSNOTIFICATIONCONTROLLER_H

#include <QObject>
#include <QQuickItem>

class NaiSysNotificationController : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(NaiSysNotification)
    QML_SINGLETON

public:
    enum class NotificationType {
        INFO,
        MESSAGE,
        WARNING,
        ERROR
    };
    Q_ENUM(NotificationType)
public:
    NaiSysNotificationController();
    virtual ~NaiSysNotificationController();

signals:
    void newNotification(int _type, const QString _message);

public://Invokable methods
    Q_INVOKABLE void
    notify(const NaiSysNotificationController::NotificationType _type,
           const QString &_message);

};

#endif // NAISYSNOTIFICATIONCONTROLLER_H
