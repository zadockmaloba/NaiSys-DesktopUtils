#ifndef NAISYS_SERVERLANG_PARSER_H
#define NAISYS_SERVERLANG_PARSER_H

#include <QObject>
#include <QFile>
#include <QStringList>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QRegularExpression>

#include <iostream>

#include "serverlangsyntaxtree.h"

namespace NaiSys {
namespace ServerLang {

class parser
{

public:
    parser();
    parser(const QString& entryFileName, const QString& pwd = "");

    void READ();

public://getters and setters
    const QString &data() const
    {
        return m_data;
    }
    void setData(const QString &newData)
    {
        m_data = newData;
    }

    const QString &fileName() const
    {
        return m_fileName;
    }
    void setFileName(const QString &newFileName)
    {
        m_fileName = newFileName;
    }

    const QString &workingDir() const
    {
        return m_workingDir;
    }
    void setWorkingDir(const QString &newWorkingDir)
    {
        m_workingDir = newWorkingDir;
    }

private://methods


private:
    QString m_fileName,
    m_data, m_workingDir;
    ServerLang::SyntaxTree m_globalAST;

private:
    static const QRegularExpression fnmatch;
    static const QRegularExpression parammatch;
    static const QRegularExpression varmatch;
    static const QRegularExpression importmatch;
};

} // namespace ServerLang
} // namespace NaiSys

#endif // NAISYS_SERVERLANG_PARSER_H
