#include "naisyssettings.h"

namespace NaiSys {

NaiSysSettings::NaiSysSettings(QObject *parent)
    : QObject{parent}
{
}

QSettings *NaiSysSettings::settings()
{
    return m_settings.get();
}

void NaiSysSettings::init()
{
    m_settings = std::make_unique<QSettings>(new QSettings);
}

void NaiSysSettings::init(const char* appName, const char* orgName)
{
    m_settings = std::make_unique<QSettings>(new QSettings{QString(orgName), QString(appName)});
}

NaiSysSettings::settings_ptr m_settings = {};

}
