#include "naisysprint.h"

#include <qdatetime.h>

NaiSysPrint::NaiSysPrint(QObject *parent)
    : QObject{parent},
      m_availablePrinters(QPrinterInfo::availablePrinters())
{

}

void NaiSysPrint::addPrinter([[maybe_unused]]QWidget* parent)
{
    return;
}

void NaiSysPrint::configurePrinter([[maybe_unused]]const QPrinter *_prntr, [[maybe_unused]]QWidget* parent)
{
    return;
}

void NaiSysPrint::printDocument(const QString &printData)
{
    if(m_selectedPrinterInfo.isNull())
    {
        qDebug() << "No printer selected";
        current_printer = new QPrinter();
        current_printer->setOutputFileName(NaiSys::SystemConfig::getRootApplicationFolder()
                                    +"printout_"+QDateTime::currentDateTime()
                                    .toString("yyyyMMdd_hhmm_ss").toLower().replace(" ","_"));
        current_printer->setOutputFormat(QPrinter::OutputFormat::PdfFormat);
        qDebug() << current_printer->outputFileName();
    }
    else{
        current_printer = new QPrinter(this->m_selectedPrinterInfo);//TODO: Fix memory leaks
    }
    QPainter _paint;
    //auto const paged_painter = current_printer->paintEngine()->paintDevice()->pa
    qDebug()<< current_printer->printerName();
    qDebug() << current_printer->printEngine()->printerState();

    if(!_paint.begin(current_printer)){ //TODO
        qDebug() << "[PRINT_ERROR]: Paint Device not open";
        qWarning("failed to open file, is it writable?");
                return;
    }

    QTextDocument doc; QTextCursor cur(&doc);
    doc.setPageSize(current_printer->pageRect(QPrinter::Unit::DevicePixel).size());
    qDebug() << doc.pageSize();
    cur.insertHtml(printData);
    //doc.
    doc.drawContents(&_paint);
    qDebug() << doc.size();
    for(auto i = doc.size().height()/doc.pageSize().height(); i > 0; --i) {
        current_printer->newPage();
    }
    _paint.end();
    return;
}

QString NaiSysPrint::fillDocumentData(const QByteArray &_data, QString _docTemplate)
{
    const auto var1 = NaiSysJsonObject::jsonDocToStringArr(_data);
    for(int i = 0; i < var1.size(); ++i){
        _docTemplate.replace("_?"+QString::number(i+1)+"_", var1[i]);
        qDebug() << "&*** "<<"_?"+QString::number(i+1)+"_"<<" : "<<var1[i];
    }
    auto const _time = QDateTime::fromString(
                QJsonDocument::fromJson(_data)
                .object().value("TransTime").toString(), "yyyyMMddHHmmss");
    _docTemplate.replace("_%DATE%_", _time.date().toString());
    _docTemplate.replace("_%TIME%_", _time.time().toString());
    return _docTemplate;
}

const QList<QPrinterInfo> &NaiSysPrint::availablePrinters() const
{
    return m_availablePrinters;
}

void NaiSysPrint::setAvailablePrinters(const QList<QPrinterInfo> &newAvailablePrinters)
{
    m_availablePrinters = newAvailablePrinters;
}

QPrinterInfo NaiSysPrint::selectedPrinterInfo() const
{
    return m_selectedPrinterInfo;
}

void NaiSysPrint::setSelectedPrinterInfo(QPrinterInfo newSelectedPrinterInfo)
{
    m_selectedPrinterInfo = newSelectedPrinterInfo;
}

bool NaiSysPrint::printJsonDocument(const QJsonObject &obj, int docHandle, const QJsonObject& format)
{
    auto const a = format.toVariantMap();
    NaiSys::NaiSysDocumentHandler docH(obj, docHandle);

    for (auto const &v : a.keys()) {
        docH.insertIntoFormatMap(v, a.value(v).toString());
    }

    auto const _dat = docH.renderDocument();

    m_selectedPrinterInfo = QPrinterInfo::printerInfo(docH.defaultPrinterName());

    qDebug() << "{{DEFAULT_PRINTER}} :: " << docH.defaultPrinterName();
    qDebug() << m_selectedPrinterInfo;

    this->printDocument(_dat);

    return 1;
}

QString NaiSysPrint::jsonToHtmlTable(const QJsonArray &jarr)
{
    return NaiSys::NaiSysDocumentHandler::jsonValsToHtmlTable(jarr);
}

QJsonArray NaiSysPrint::json_availablePrinters()
{
    auto _list = this->availablePrinters();
    QJsonArray arr;
    for(auto &v : _list){
        QJsonObject obj;
        obj.insert("Name", QJsonValue(v.printerName()));
        obj.insert("Default", QJsonValue(v.isDefault()));
        arr.append(QJsonValue(obj));
    }

    return arr;
}

QJsonObject NaiSysPrint::json_printerInfo(const QString &printername)
{
    auto const dat = QPrinterInfo::printerInfo(printername);
    QJsonObject obj;
    obj.insert("Name", QJsonValue(dat.printerName()));
    obj.insert("Make", QJsonValue(dat.makeAndModel()));
    obj.insert("Location", QJsonValue(dat.location()));
    obj.insert("Default", QJsonValue(dat.isDefault()));
    obj.insert("Description", QJsonValue(dat.description()));
    obj.insert("State", QJsonValue(dat.state()));

    return obj;
}
