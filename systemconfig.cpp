#include "systemconfig.h"

namespace NaiSys {

SystemConfig::SystemConfig()
{

}

const QString &SystemConfig::rootConfigFolder() const
{return m_rootConfigFolder;}

void SystemConfig::setRootConfigFolder(const QString &newRootConfigFolder)
{m_rootConfigFolder = newRootConfigFolder;}

const QString &SystemConfig::rootWebSiteFolder() const
{return m_rootTemplateFolder;}

void SystemConfig::setRootTemplateFolder(const QString &newRootWebSiteFolder)
{m_rootTemplateFolder = newRootWebSiteFolder;}

const QString &SystemConfig::appName() const
{return m_appName;}

void SystemConfig::setAppName(const QString &newAppName)
{m_appName = newAppName;}

const QJsonObject SystemConfig::m_sInitData = { //TODO: create other docs
    {"App-Name", QJsonValue("Default")},
    {"Template-Dir", QJsonValue("templates")},
    {"Default-Template", QJsonValue("default_receipt.html")},
    {"DataBase", QJsonValue("test.sqlite")},
    {"Templates", QJsonObject({
         {"Statement", QJsonObject({
              {"StatementFile", "defualt_statement.html"},
              {"StatementPrinter", QJsonValue("")}
          })},
         {"Receipt", QJsonObject({
              {"ReceiptFile", "default_receipt.html"},
              {"ReceiptPrinter", QJsonValue("")}
          })},
         {"Reconciliation", QJsonObject({
              {"ReconciliationFile", "default_reconciliation.html"},
              {"ReconciliationPrinter", QJsonValue("")}
          })},
         {"Report", QJsonObject({
              {"ReportFile", "default_report.html"},
              {"ReportPrinter", QJsonValue("")}
          })},
     })}
};

bool SystemConfig::checkForFile(const QString &filename)
{return QFile(filename).exists();}

bool SystemConfig::checkForFolder(const QString &folderpath)
{return QDir(folderpath).exists();}

void SystemConfig::createRootConfigFolder()
{

}

QJsonObject SystemConfig::readConfigFile()
{
    if(!checkForFile(__doc_dir__ +'/'+ m_sRootConfigFolder +'/'+ m_sConfigFile))
    {
        qDebug() << "File does not exist";
        createConfigFile();
        createRootTemplateFolder("");
    }
    QFile _file(__doc_dir__ +'/'+ m_sRootConfigFolder +'/'+ m_sConfigFile);
    _file.open(QIODevice::ReadOnly);
    auto const js = QJsonDocument::fromJson(_file.readAll()).object();
    _file.close();
    return js;
}

QString SystemConfig::getRootTemplateFolder()
{
    return __doc_dir__+'/'+ m_sRootConfigFolder+'/'+ m_sRootTemplateFolder+'/';
}

QString SystemConfig::getRootApplicationFolder()
{
    return __doc_dir__+'/'+ m_sRootConfigFolder+'/';
}

void SystemConfig::editConfigFile(const QString &key, const QString &newV)
{
    /*
     * FIXME: this is a very horrible implementation
     * but it get's the job done.
     * It will have to do until Qt implements an iterator
     * that can iterate through nested JsonObjects.
*/

    auto newVal = QString(newV)
            .replace('\x005C', "\\\\");

    auto obj = SystemConfig::readConfigFile();
    auto tempObj = obj;
    auto dirList = key.split("/");
    QJsonObject temp;
    QJsonObject::Iterator it;

    qDebug() << dirList;

    it = obj.find(dirList.first());

    for(int i = 0; i < dirList.size() - 1 ; ++i){
        if(it.value().isObject()){
            qDebug() << "{{OBJECT}}";
            qDebug() << it.value().toObject();
            qDebug() << i;
            temp = it.value().toObject();
            it = temp.find(dirList[i+1]);
        }
        else if(it.value().isUndefined()){
            qDebug() << "Could not find Key";
            return;
        }
        else if(it.value().isString()){
            qDebug() << "Bingo"; //TODO: Remove, unused
        }
        else {
            qDebug() << "UNDIFINED ERROR";
            return;
        }
    }

    auto itr = it;

    qDebug() << "{{"+itr.key()+"}} :: Old value "<< itr.value();
    auto const old_value = itr.value().toString();
    qDebug() << "{{"+itr.key()+"}} :: New value "<< newVal;

    qDebug() << obj;

    QFile _file(__doc_dir__ +'/'+ m_sRootConfigFolder +'/'+ m_sConfigFile);
    _file.open(QIODevice::ReadOnly);
    auto dat = QString(_file.readAll());

    auto const oldK = QString("\""+itr.key()+"\": \""+old_value+"\"");
    auto const newK = QString("\""+itr.key()+"\": \""+newVal+"\"");
    _file.close();

    qDebug() << QString(oldK);

    if(dat.contains(oldK)){
        qDebug() << "KEY_FOUND_CONFIG_FILE";

        dat.replace( oldK , newK);
    }

    _file.open(QIODevice::WriteOnly);
    _file.write(dat.toUtf8());
    _file.close();

}

void SystemConfig::createRootTemplateFolder([[maybe_unused]]const QString &foldername)
{
    QFile m_file(":/templates/templates/default-receipt.html");
    m_file.open(QIODevice::ReadOnly);
    auto const _dat =  m_file.readAll();
    m_file.close();

    QFile m_file2(":/templates/templates/default-report.html");
    m_file2.open(QIODevice::ReadOnly);
    auto const _dat2 =  m_file2.readAll();
    m_file2.close();


    auto _r = QDir(__doc_dir__).mkpath(__doc_dir__+'/'+ m_sRootConfigFolder+'/'
                                       + m_sRootTemplateFolder+'/');
    if(_r){
        QFile _file(__doc_dir__+'/'+ m_sRootConfigFolder +'/'+ m_sRootTemplateFolder+'/'
                    + m_sInitData.value("Templates")
                    .toObject().value("Receipt")
                    .toObject().value("ReceiptFile").toString());
        _file.open(QIODevice::WriteOnly);
        _file.write(_dat);
        _file.close();

        QFile _file2(__doc_dir__+'/'+ m_sRootConfigFolder +'/'+ m_sRootTemplateFolder+'/'
                    + m_sInitData.value("Templates")
                     .toObject().value("Report")
                     .toObject().value("ReportFile").toString());
        _file2.open(QIODevice::WriteOnly);
        _file2.write(_dat2);
        _file2.close();
    }

    qDebug() << QString((_r == true ) ? "Succesfully Created" : "Failed to Create");
    return;
}

void SystemConfig::createConfigFile()
{
    auto _r = QDir(__doc_dir__).mkpath(__doc_dir__+'/'+ m_sRootConfigFolder +'/');
    qDebug() << QString((_r == true ) ? "Succesfully Created" : "Failed to Create");
    if(_r){
        QFile _file(__doc_dir__+'/'+ m_sRootConfigFolder +'/'+ m_sConfigFile);
        _file.open(QIODevice::WriteOnly);
        _file.write(QJsonDocument(m_sInitData).toJson());
        _file.close();
    }
    return;
}

void RuntimeData::editSystemConfig(const QString &key, const QString &newVal)
{
    SystemConfig::editConfigFile(key, newVal);
}

} // namespace NaiSys
