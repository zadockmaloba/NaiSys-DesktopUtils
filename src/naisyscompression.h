#ifndef NAISYS_NAISYSCOMPRESSION_H
#define NAISYS_NAISYSCOMPRESSION_H

#include <QObject>
#include <QByteArray>
#include <QDebug>

#include <zlib.h>

namespace NaiSys {

class NaiSysCompression : public QObject
{
    Q_OBJECT
public:
    explicit NaiSysCompression(QObject *parent = nullptr);
    static const QByteArray jpegDecompress(const QByteArray &data);
    static const QByteArray jpegCompress(const QByteArray &data);

signals:

};

} // namespace NaiSys

#endif // NAISYS_NAISYSCOMPRESSION_H
