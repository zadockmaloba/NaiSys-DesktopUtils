#include "naisysapplicationcontroller.h"

QJsonArray NaiSysApplicationController::m_appModel = {};

NaiSysApplicationController::NaiSysApplicationController()
{

}

QJsonArray NaiSysApplicationController::appModel()
{
    return m_appModel;
}

void NaiSysApplicationController::setAppModel(const QJsonArray &newAppModel)
{
    m_appModel = newAppModel;
}
