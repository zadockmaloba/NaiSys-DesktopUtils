#ifndef NAISYSSETTINGS_H
#define NAISYSSETTINGS_H

#include <QObject>
#include <QSettings>
#include <memory>

namespace NaiSys {

class NaiSysSettings : public QObject
{
    Q_OBJECT
public:
    using settings_ptr = std::unique_ptr<QSettings>;
public:
    explicit NaiSysSettings(QObject *parent = nullptr);

    static QSettings *settings();
    static void init();
    static void init(const char* appName, const char* orgName);

signals:
    void settingsChanged(const QString &key, const QString &value);

private:
    static settings_ptr m_settings;
};

}

#endif // NAISYSSETTINGS_H
