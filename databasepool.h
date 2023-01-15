#ifndef NAISYS_DATABASEPOOL_H
#define NAISYS_DATABASEPOOL_H

#include <QObject>
#include <QString>

#include <vector>
#include <memory.h>

#include "databasehandler.h"

namespace NaiSys {

typedef std::shared_ptr<DatabaseHandler> db_shared_ptr;
typedef std::pair<const QString, const db_shared_ptr> dblist_field;
typedef std::list<dblist_field> dblist;

class DatabasePool : public QObject
{
    Q_OBJECT
public:
    explicit DatabasePool(QObject *parent = nullptr);
    DatabasePool(const std::initializer_list<db_shared_ptr> &list, QObject *parent = nullptr);

    const dblist_field find(const QString &key);
    void insert(const dblist_field &field);
    bool remove(const QString &key);

signals:

private:
    dblist m_databaseMap;
};

} // namespace naisys

#endif // NAISYS_DATABASEPOOL_H
