#include "serverobject.h"

namespace NaiSys {

ServerObject::ServerObject(QObject *parent)
    : QThread{ parent }
{

}

ServerObject::ServerObject(const server_params &prms, QObject *parent)
    : QThread{ parent },
      m_serverParams{ prms }
{

}

const server_params &ServerObject::serverParams() const
{
    return m_serverParams;
}

void ServerObject::setServerParams(const server_params &newServerParams)
{
    m_serverParams = newServerParams;
}

} // namespace NaiSys
