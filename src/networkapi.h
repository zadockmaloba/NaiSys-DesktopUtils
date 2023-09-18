#ifndef NETWORKAPI_H
#define NETWORKAPI_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <memory>
#include <map>

class NetworkController : public QObject
{
    Q_OBJECT
public:
    using netman_ptr = std::unique_ptr<QNetworkAccessManager>;
    using req_ptr = std::unique_ptr<QNetworkRequest>;
    using job_map = std::map<int, req_ptr>;

public:
    explicit NetworkController(QObject *parent = nullptr);

public:
    static QNetworkAccessManager* netManager();
    static const job_map &requestHeap();
    Q_INVOKABLE static void createPushRequest(const QString& path, const QByteArray &data);
    Q_INVOKABLE static QByteArray createPushRequestAwait(const QString& path, const QByteArray &data);
    Q_INVOKABLE static void createGetRequest(const QString& path, const QByteArray &data={});
    Q_INVOKABLE static QByteArray createGetRequestAwait(const QString& path, const QByteArray &data={});

    Q_INVOKABLE static void createPushRequestSecure(const QString& path, const QByteArray &data);
    Q_INVOKABLE static QByteArray createPushRequestAwaitSecure(const QString& path, const QByteArray &data);
    Q_INVOKABLE static void createGetRequestSecure(const QString& path, const QByteArray &data={});
    Q_INVOKABLE static QByteArray createGetRequestAwaitSecure(const QString& path, const QByteArray &data={});

    static QString serverHost();
    static void setServerHost(const QString &newServerHost);

    static int serverPort();
    static void setServerPort(int newServerPort);

public slots:
    void onRequestComplete();

private:
    static netman_ptr m_netManager;
    static job_map m_requestHeap;
    static QString m_serverHost;
    static int m_serverPort;

signals:

};

inline NetworkController::netman_ptr NetworkController::m_netManager = std::make_unique<QNetworkAccessManager>();
inline NetworkController::job_map NetworkController::m_requestHeap = {};
inline QString NetworkController::m_serverHost = "google.com";
inline int NetworkController::m_serverPort = 80;

#endif // NETWORKAPI_H
