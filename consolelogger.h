#ifndef NAISYS_CONSOLELOGGER_H
#define NAISYS_CONSOLELOGGER_H



#include <QObject>
#include <QDebug>

namespace NaiSys {

class  ConsoleLogger : public QObject
{
    Q_OBJECT
public:
    explicit ConsoleLogger(QObject *parent = nullptr);
    Q_INVOKABLE const QString readLogBuffer();
    Q_INVOKABLE void writeToLogBuffer(const QString &data);

signals:

private:
    QString m_LogBuffer;

};

} // namespace NaiSys

#endif // NAISYS_CONSOLELOGGER_H
