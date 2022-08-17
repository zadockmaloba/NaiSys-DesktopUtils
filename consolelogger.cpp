#include "consolelogger.h"

namespace NaiSys {

ConsoleLogger::ConsoleLogger(QObject *parent)
    : QObject{parent},
      m_LogBuffer{"Console Log... \r\n"}
{

}

const QString ConsoleLogger::readLogBuffer()
{
    QString ret;
    NAISYS_BUFFER_DEV(s, dev)
    while(dev.canReadLine()){
        ret.append(QString::fromStdString(dev.readLine())+"\n");
    }
    return ret;
}

void ConsoleLogger::writeToLogBuffer(const QString &data)
{
    m_msgCounter += 1;
    m_LogBuffer.append(data + "\n");
}

const QJsonArray ConsoleLogger::readJsonLogBuffer()
{
    QJsonArray arr;
    updateLogAPI();

    for(auto &v : m_msgMap){
        int _id; QTime _time; QString _dat;
        std::tie(_id, _time, _dat) = v;

        QJsonObject jobj ={
            {"msg_id",   QJsonValue(_id)},
            {"msg_time", QJsonValue(_time.toString())},
            {"msg_data", QJsonValue(_dat)}
        };
        arr.append(jobj);
    }
    return arr;
}

bool ConsoleLogger::bufferUpdated()
{
    NAISYS_BUFFER_DEV(s, dev)
    return dev.lineCount() > (int)m_msgMap.size();
}

void ConsoleLogger::updateLogAPI()
{
    NAISYS_BUFFER_DEV(s, dev)
    if(dev.lineCount() - (int)m_msgMap.size()){
        if(m_msgMap.size()) dev.setCursor(m_msgMap.size()-1);
        while(dev.canReadLine()){
            m_msgMap.push_back({m_msgCounter,
                                QTime::currentTime(),
                                QString::fromStdString(dev.readLine())});
            m_msgCounter += 1;
        }
    }
}

} // namespace NaiSys
