#include "consolelogger.h"

namespace NaiSys {

ConsoleLogger::ConsoleLogger(QObject *parent)
    : QObject{parent},
      m_LogBuffer{"Console Log... \r\n"}
{

}

const QString ConsoleLogger::readLogBuffer()
{
    qDebug() << "FUNCTION CALLED";
    return m_LogBuffer;
}

void ConsoleLogger::writeToLogBuffer(const QString &data)
{
    m_LogBuffer.append(data + "\n");
}

} // namespace NaiSys
