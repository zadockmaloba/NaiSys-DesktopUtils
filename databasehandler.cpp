#include "databasehandler.h"

namespace NaiSys {

DatabaseHandler::DatabaseHandler(QObject *parent)
    : QObject{parent}
{

}

DatabaseHandler::DatabaseHandler(const QSqlDatabase &dbH, QObject *parent)
    : QObject{parent},
      m_dbHandle{dbH}
{

}

DatabaseHandler::DatabaseHandler(const QString &connectionName, const QString &databaseName, const QString &db, QObject *parent)
    : QObject{parent},
      m_dbName{databaseName},
      m_dbConnectionName{connectionName},
      m_dbType{db}
{
    this->m_dbHandle = QSqlDatabase::addDatabase(m_dbType, m_dbConnectionName);

    if(m_dbType == "QPSQL"){
        if(READFROMCONFIG){
            qDebug() << "{{DATABASEHANDLER - QPSQL}} :: READING FROM CONFIG FILE";
            auto const obj = SystemConfig::readConfigFile().value("DataBase").toObject();
            qDebug() << obj;

            this->m_dbHandle.setHostName(obj.value("DbHostName").toString());
            this->m_dbHandle.setPort(obj.value("DbPort").toInt());
            this->m_dbHandle.setUserName(obj.value("DbUser").toString());
            this->m_dbHandle.setPassword(obj.value("DbPassword").toString());
        }
        else {
            this->m_dbHandle.setHostName("localhost");
            this->m_dbHandle.setPort(5432);
            this->m_dbHandle.setUserName("postgres");
            this->m_dbHandle.setPassword("postgres");
        }
    }

    this->m_dbHandle.setDatabaseName(m_dbName);
}

void DatabaseHandler::initialiseDb()
{
    this->m_dbHandle = QSqlDatabase::addDatabase("QSQLITE", m_dbConnectionName);
    this->m_dbHandle.setDatabaseName(m_dbName);
}

const QSqlDatabase &DatabaseHandler::dbHandle() const
{return m_dbHandle;}

void DatabaseHandler::setDbHandle(const QSqlDatabase &newDbHandle)
{m_dbHandle = newDbHandle;}

const QString &DatabaseHandler::dbName() const
{return m_dbName;}

void DatabaseHandler::setDbName(const QString &newDbName)
{m_dbName = newDbName;}

const QString &DatabaseHandler::dbConnectionName() const
{return m_dbConnectionName;}

void DatabaseHandler::setDbConnectionName(const QString &newDbConnectionName)
{m_dbConnectionName = newDbConnectionName;}

void DatabaseHandler::reConnectDb()
{
    return; //:^}
}

bool DatabaseHandler::createAndOrInsertRowToTable(const QString &tableName, const QJsonObject &_dat)
{
    //auto const _dat = QJsonDocument::fromJson(data.toUtf8()).object();

    this->openDatabaseSocket();
    auto const availableTables = this->m_dbHandle.tables();
    this->closeDatabaseSocket();

    auto const colStringList = _dat.keys();
    auto const valStringList = _dat.toVariantMap().values();

//    std::function <void()> _f([&]() mutable {

//        return;
//        });

//    auto thread = new DataBaseWorker(_f);
//    QObject::connect(thread, &QThread::finished, thread, &QThread::deleteLater);
//    thread->start();

    QString colString, valString;

    for(auto const &v : colStringList) colString.append(v.toLower()+",");
    colString.chop(1);

    for(auto const &v : valStringList) valString.append("'"+
                                                        v.toString()
                                                        .replace("'", "''")
                                                        +"',");
    valString.chop(1);

    if(colString.contains(",TransID", Qt::CaseSensitivity::CaseInsensitive)
            || colString.contains(",ID ", Qt::CaseSensitivity::CaseInsensitive))
        colString.replace(",transid", ",transid UNIQUE PRIMARY KEY NOT NULL"); //TODO: Use REGEX

    auto const crt = QString("CREATE TABLE IF NOT EXISTS "+tableName+" ( "+colString+" );");

    if(colString.contains("UNIQUE PRIMARY KEY NOT NULL", Qt::CaseSensitivity::CaseInsensitive))
        colString.replace("UNIQUE PRIMARY KEY NOT NULL", " ");
    auto const a = QString("INSERT INTO "+tableName+" ( "+colString+" ) VALUES ( "+valString+" );");

    if(!availableTables.contains(tableName)){
        auto ptr_a = this->runSqlQuerry(crt);
        ptr_a->deleteLater();
    }

    auto ptr_b = this->runSqlQuerry(a);
    ptr_b->deleteLater();


    return 1;
}

bool DatabaseHandler::openDatabaseSocket()
{
    qDebug() << "ATTEMPTING TO CONNECT DATABASE";
    return m_dbHandle.open();
}

bool DatabaseHandler::closeDatabaseSocket()
{
    m_dbHandle.close();
    return true; //:^}
}

const QString &DatabaseHandler::dbType() const
{return m_dbType;}

void DatabaseHandler::setDbType(const QString &newDbType)
{m_dbType = newDbType;}

inline QSqlQueryModel *DatabaseHandler::runSqlQuerry(const QString &querry)
{
    this->openDatabaseSocket();
    auto m_model = new QSqlQueryModel; //TODO: Fix leak
    m_model->setQuery(querry, m_dbHandle);
    qDebug() << "{"+m_dbName+"} "<< "[ "+querry+" ]: "<< m_model->lastError().text();
    this->closeDatabaseSocket();
    return m_model;
}

const QString DatabaseHandler::json_runSqlQuerry(const QString &querry)
{
    this->openDatabaseSocket();
    auto m_model = new QSqlQueryModel; //TODO: Fix leak
    m_model->setQuery(querry, m_dbHandle);
    qDebug() << "{"+m_dbName+"} "<< "[ "+querry+" ]: "<< m_model->lastError().text();
    this->closeDatabaseSocket();

    auto const resp = NaiSysJsonObject::qryModelToJson(m_model);

    m_model->deleteLater();

    return resp;
}

} // namespace NaiSys
