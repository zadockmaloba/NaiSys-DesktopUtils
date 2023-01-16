#ifndef NAISYS_CONSOLELOGGER_H
#define NAISYS_CONSOLELOGGER_H



#include <QObject>
#include <QDebug>
#include <QTime>

#include <QJsonObject>
#include <QJsonArray>

#include <vector>
#include <tuple>
#include <ostream>

#include "streamio.h"

namespace NaiSys {

class  ConsoleLogger : public QObject
{
    Q_OBJECT
public:
    explicit ConsoleLogger(QObject *parent = nullptr);
    Q_INVOKABLE const QString readLogBuffer();
    Q_INVOKABLE void writeToLogBuffer(const QString &data);
    Q_INVOKABLE const QJsonArray readJsonLogBuffer();
    Q_INVOKABLE bool bufferUpdated();

signals:

private:
    void updateLogAPI();

private:
    QString m_LogBuffer;
    QTime m_msgTime;
    int m_msgCounter = 0;
    std::vector<std::tuple<int, QTime, QString>> m_msgMap;
};

} // namespace NaiSys

#endif // NAISYS_CONSOLELOGGER_H
