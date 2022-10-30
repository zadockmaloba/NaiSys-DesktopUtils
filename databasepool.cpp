#include "databasepool.h"
#include <algorithm>

namespace NaiSys {

DatabasePool::DatabasePool(QObject *parent)
    : QObject{parent}
{

}

DatabasePool::DatabasePool(const std::initializer_list<db_shared_ptr> &list, QObject *parent)
    : QObject{parent}
{
    for(auto const &v : list){
        m_databaseMap.push_back({v->dbConnectionName(), v});
    }

}

const dblist_field DatabasePool::find(const QString &key)
{
    QString ret_str;
    db_shared_ptr ret_ptr;
    std::for_each(m_databaseMap.begin(), m_databaseMap.end(),
                  [&](dblist_field &v)mutable{
        if(v.first == key){
            ret_str = v.first;
            ret_ptr = v.second;
        };
        //v.first == key ? ret.swap(v): ret.swap(dblist_field{""});
    });

    return dblist_field{ret_str, ret_ptr};
}

void DatabasePool::insert(const dblist_field &field)
{
    m_databaseMap.push_back(field);
}

bool DatabasePool::remove(const QString &key)
{
    bool stat = false;
    std::for_each(m_databaseMap.begin(), m_databaseMap.end(),
                  [&](dblist_field &v)mutable{
        if(v.first == key) m_databaseMap.remove(v);
    });
    return stat;
}

} // namespace NaiSys
