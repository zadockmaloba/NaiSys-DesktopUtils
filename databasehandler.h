#ifndef NAISYS_DATABASEHANDLER_H
#define NAISYS_DATABASEHANDLER_H

#ifdef NAISYS_READFROMCONFIG
#define READFROMCONFIG 1
#else
#define READFROMCONFIG 0
#endif

#include <QObject>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QJsonObject>
#include <QJsonValue>
#include <QSqlError>
#include <QDebug>

#include <QThread>

#include "systemconfig.h"
#include "naisysjsonobject.h"

namespace NaiSys {

class  DatabaseHandler : public QObject
{
    Q_OBJECT
private:
    class DataBaseWorker : public QThread
    {
    private:
        //void (*m_lambda)();
        std::function<void()> m_lambda;


    public:
        DataBaseWorker(const std::function<void()> &lmbd, QObject *parent = Q_NULLPTR)
            : QThread{parent}
            , m_lambda{lmbd}
        {
            qDebug() << "{{DATABASE_WORKER}} :: STARTING_THREAD";
        }

        ~DataBaseWorker(){
            qDebug() << "{{DATABASE_WORKER}} :: CLOSING_THREAD";
        }

        void run(){
            m_lambda();
            this->exit(0);
        }
    };

public:
    explicit DatabaseHandler(QObject *parent = nullptr);
    DatabaseHandler(const QSqlDatabase &dbH, QObject *parent = nullptr);
    DatabaseHandler(const QString &connectionName, const QString &databaseName, const QString &dbType = "QSQLITE", QObject *parent = nullptr);
    void initialiseDb();
    void reConnectDb();
    Q_INVOKABLE bool createAndOrInsertRowToTable(const QString &tableName, const QJsonObject &data);

    const QSqlDatabase &dbHandle() const;
    void setDbHandle(const QSqlDatabase &newDbHandle);
    const QString &dbName() const;
    void setDbName(const QString &newDbName);
    const QString &dbConnectionName() const;
    void setDbConnectionName(const QString &newDbConnectionName);
    QSqlQueryModel *runSqlQuerry(const QString &querry); //
    Q_INVOKABLE const QString json_runSqlQuerry(const QString &querry);

    const QString &dbType() const;
    void setDbType(const QString &newDbType);

signals:

private://methods
    bool openDatabaseSocket();
    bool closeDatabaseSocket();

private://members
    QSqlDatabase m_dbHandle;
    QString m_dbName, m_dbConnectionName, m_dbType;
};

} // namespace NaiSys

#endif // NAISYS_DATABASEHANDLER_H
