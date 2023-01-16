#ifndef NAISYS_SERVEROBJECT_H
#define NAISYS_SERVEROBJECT_H

#include <QThread>
#include <QString>
#include <QObject>

namespace NaiSys {

struct server_params {
    int Port;
    bool Ssl;
    QString Address,
        Ssl_Cert,
        Ssl_Key,
        Entry_Script,
        Site_Dir;
};
class ServerObject : public QThread
{
    Q_OBJECT
public:
    explicit ServerObject(QObject *parent = nullptr);
    ServerObject(const server_params &prms, QObject *parent = nullptr);
    //virtual ~ServerObject();

    const server_params &serverParams() const;
    void setServerParams(const server_params &newServerParams);

private:
    server_params m_serverParams;
};

} // namespace NaiSys

#endif // NAISYS_SERVEROBJECT_H
