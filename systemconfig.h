#ifndef NAISYS_SYSTEMCONFIG_H
#define NAISYS_SYSTEMCONFIG_H

#define __doc_dir__ QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)

#include <QObject>
#include <QDebug>
#include <QStandardPaths>
#include <QFile>
#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>

#include <string>

namespace NaiSys {

class RuntimeData : public QObject
{
    Q_OBJECT
public:
    RuntimeData(QObject *parent = Q_NULLPTR)
        : QObject{parent}
    {}

    Q_INVOKABLE void setServerAddress(const QString &newServerAddress)
    {m_serverAddress = newServerAddress;}

    Q_INVOKABLE const QString serverAddress() const
    {return m_serverAddress;}

    Q_INVOKABLE const QString selectedBranch() const
    {return m_selectedBranch;}

    Q_INVOKABLE void setSelectedBranch(const QString &newSelectedBranch)
    {m_selectedBranch = newSelectedBranch;}

    Q_INVOKABLE const QString selectedBranchName() const
    {return m_selectedBranchName;}

    Q_INVOKABLE void setSelectedBranchName(const QString &newSelectedBranchName)
    {m_selectedBranchName = newSelectedBranchName;}

    Q_INVOKABLE void editSystemConfig(const QString &key, const QString &newVal);

private:
    QString m_serverAddress;
    QString m_selectedBranch;
    QString m_selectedBranchName;
};


class SystemConfig
{
public:
    SystemConfig();
    const QString &rootConfigFolder() const;
    void setRootConfigFolder(const QString &newRootConfigFolder);
    const QString &rootWebSiteFolder() const;
    void setRootTemplateFolder(const QString &newRootWebSiteFolder);
    const QString &appName() const;
    void setAppName(const QString &newAppName);

public: //static methods
    static bool checkForFile(const QString &filename);
    static bool checkForFolder(const QString &folderpath);
    static void setRootFolderName(const QString &fname);
    static void createRootConfigFolder();
    static QJsonObject readConfigFile();
    static QString getRootTemplateFolder();
    static QString getRootApplicationFolder();
    static void editConfigFile(const QString &key, const QString &newVal);
    static void insertToConfigFile(const QString &key, const QJsonValue &newVal);

    char *sRootTemplateFolder() const;
    void setSRootTemplateFolder(char *newSRootWebSiteFolder);

    static const QString createPath(const QString &path);

private:
    static void createRootTemplateFolder(const QString &foldername = "templates");
    static void createConfigFile();

private:
    static QString m_sRootConfigFolder;
    static constexpr char m_sRootTemplateFolder[] {"templates"};
    static constexpr char m_sConfigFile[] {"appconfig.json"};
    static const QJsonObject m_sInitData;

private:
    QString m_rootConfigFolder;
    QString m_rootTemplateFolder;
    QString m_appName;
};

} // namespace NaiSys

#endif // NAISYS_SYSTEMCONFIG_H
