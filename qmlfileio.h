#ifndef NAISYS_QMLFILEIO_H
#define NAISYS_QMLFILEIO_H

#include <QObject>
#include <QFile>
#include <QUrl>
#include <QDebug>

namespace NaiSys {

class QmlFileIO : public QObject
{
    Q_OBJECT
public:
    explicit QmlFileIO(QObject *parent = nullptr);
    Q_INVOKABLE static const QString readTextFile(const QString &fURL);
    Q_INVOKABLE static bool writeTextFile(const QString &fURL, const QString &data);
    Q_INVOKABLE static const QByteArray readBinaryFile(const QString &fURL);
    Q_INVOKABLE static const bool writeBinaryFile(const QString &fURL, const QByteArray &data);

signals:

};

} // namespace NaiSys

#endif // NAISYS_QMLFILEIO_H
