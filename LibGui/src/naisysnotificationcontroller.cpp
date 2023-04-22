#include "naisysnotificationcontroller.h"

NaiSysNotificationController::NaiSysNotificationController()
{

}

NaiSysNotificationController::~NaiSysNotificationController()
{

}

void NaiSysNotificationController::
notify(const NotificationType _type, const QString &_message)
{
    qDebug() << _type << " : " << _message;

    emit newNotification(static_cast<int>(_type), _message);
}
