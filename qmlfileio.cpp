#include "qmlfileio.h"

namespace NaiSys {

QmlFileIO::QmlFileIO(QObject *parent)
    : QObject{parent}
{

}

const QString QmlFileIO::readTextFile(const QString &fURL)
{
    auto const _url = QUrl(fURL);
    QFile m_file(_url.path());
    m_file.open(QIODevice::ReadOnly) ?
                qDebug() << "{{FILE_IO}} :: "<<m_file.fileName()<<" opened.":
                qDebug() << "{{FILE_IO}} :: "<<m_file.fileName()<<" not found.";
    auto const _dat = m_file.readAll();
    m_file.close();
    return _dat;
}

bool QmlFileIO::writeTextFile(const QString &fURL, const QString &data)
{
    auto const _url = QUrl(fURL);
    QFile m_file(_url.path());
    m_file.open(QIODevice::WriteOnly) ?
                qDebug() << "{{FILE_IO}} :: "<<m_file.fileName()<<" opened.":
                qDebug() << "{{FILE_IO}} :: "<<m_file.fileName()<<" Error creating file.";

    if(m_file.write(data.toUtf8()) == data.toUtf8().size()){
        m_file.close();
        return true;
    }
    m_file.close();
    qDebug() << "{{FILE_IO}} :: Write process incomplete.";
    return false;
}

const QByteArray QmlFileIO::readBinaryFile(const QString &fURL)
{
    auto const _url = QUrl(fURL);
    QFile m_file(_url.path());
    m_file.open(QIODevice::ReadOnly) ?
                qDebug() << "{{FILE_IO}} :: "<<m_file.fileName()<<" opened.":
                qDebug() << "{{FILE_IO}} :: "<<m_file.fileName()<<" not found.";
    auto const bytesAvailable = m_file.bytesAvailable();
    auto const dat = m_file.read(bytesAvailable);
    qDebug() << "{{FILE_IO}} :: Bytes read: " << dat.size() << " / "<<bytesAvailable;
    m_file.close();
    return dat;
}

bool QmlFileIO::writeBinaryFile(const QString &fURL, const QByteArray &data)
{
    fURL;data;
    return true; //TODO: implement
}

} // namespace NaiSys
