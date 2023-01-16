#include "naisyscompression.h"

namespace NaiSys {

NaiSysCompression::NaiSysCompression(QObject *parent)
    : QObject{parent}
{

}

const QByteArray NaiSysCompression::jpegDecompress(const QByteArray &data)
{
    return QByteArray();

}

const QByteArray NaiSysCompression::jpegCompress(const QByteArray &data)
{
//    qDebug() << "{{Z_LIB}} :: Starting Compress";
//    auto const tmp = data;
//    QDataStream dstrm(tmp);
//    QByteArray val;
//    qDebug() << dstrm.device();

//    z_stream zstr;
//    zstr.zalloc = Z_NULL;
//    zstr.zfree = Z_NULL;
//    zstr.opaque = Z_NULL;
//    int ret = deflateInit(&zstr, Z_BEST_COMPRESSION);
//    qDebug() << "Starting deflate";
//    if( Z_OK != ret){
//        qWarning("{{Z_LIB}} :: Compression failure");
//        return data;
//    }
//    const int BUF = 1024;
//    Bytef in[BUF];
//    Bytef out[BUF];
//    do{
//        int readSize = dstrm.readRawData((char *)in, BUF);
//        qDebug() << "{{Z_LIB}} :: Read Size: "<< readSize;
//        zstr.avail_in = readSize;
//        zstr.next_in = in;

//        int flush = Z_NO_FLUSH;
//        if(readSize == 0) flush = Z_FINISH;
//        {
//            zstr.avail_out = BUF;
//            zstr.next_out = out;

//            if(readSize != 0){
//                qDebug() << "NO_NULL";
//                val.append(QByteArray::fromRawData((const char*)out, BUF));
//                ret = deflate(&zstr, flush);
//            }
//            else ret = Z_STREAM_END;
//        }
//    }while(ret != Z_STREAM_END);

//    deflateEnd(&zstr);

//    qDebug() << "{{ZLIB}} :: Compressed size: "<<val.size();

//    return val;
}

} // namespace NaiSys
