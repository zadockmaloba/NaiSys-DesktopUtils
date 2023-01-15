#include "naisysdocumenthandler.h"

namespace NaiSys {

const QStringList NaiSysDocumentHandler::jsonValsToStringList(const QJsonObject &obj)
{
    auto ret = QStringList();
    auto const v = obj.toVariantMap().values();
    for (auto &a : v) ret.append(a.toString());
    return ret;
}

const QString NaiSysDocumentHandler::jsonValsToHtmlTable(const QJsonArray &jarr)
{
    auto ret = QString("<table>");
    auto header = jarr.at(0).toObject().keys();

    // Table Headers
    ret.append("<tr>");
    for (auto const &v : header) ret.append("<th>"+v.toUpper()+"</th>");
    ret.append("</tr>");

    // Table Body
    for(auto &obj : jarr){
        auto vals = NaiSysDocumentHandler::jsonValsToStringList(obj.toObject());
        ret.append("<tr>");
        for(auto const &v : vals) ret.append("<td>"+v+"</td>");
        ret.append("</tr>");
    }
    ret.append("</table>");
    return ret;
}

NaiSysDocumentHandler::NaiSysDocumentHandler()
{
    
}

NaiSysDocumentHandler::NaiSysDocumentHandler(const QStringList &datString)
{
    
}

NaiSysDocumentHandler::NaiSysDocumentHandler(const DocumentStruct &docStruct)
{
    
}

NaiSysDocumentHandler::NaiSysDocumentHandler(const QJsonObject &datObject, int templateHandle)
    : m_docStruct{
          templateHandle,
          NaiSysDocumentHandler::jsonValsToStringList(datObject)
      },
      m_templatesObject {SystemConfig::readConfigFile().value("Templates").toObject()},
      m_dataObject {datObject},
      m_templateHandle {templateHandle}
{
    qDebug() << m_templatesObject;
}

NaiSysDocumentHandler::NaiSysDocumentHandler(const QStringList &datString, int templateHandle)
{
    
}

const QString &NaiSysDocumentHandler::renderDocument()
{
    switch (m_templateHandle) {
    case DocTypes::Receipt: {

        m_defaultPrinterName = m_templatesObject.value("Receipt")
                .toObject().value("ReceiptPrinter")
                .toString();

        qDebug() << "{{DEFAULT_PRINTER_NAME}} :: "<< m_defaultPrinterName;

        QFile m_file(SystemConfig::getRootApplicationFolder()
                     +m_templatesObject.value("Receipt")
                     .toObject().value("ReceiptFile").toString());

        m_file.open(QIODevice::ReadOnly);
        m_templateString = QString(m_file.readAll());
        m_file.close();

        auto const map = m_dataObject.toVariantMap();

        for (auto const &v : m_formatMap.keys()) {
            m_templateString.replace("_%"+v.toUpper()+"%_", m_formatMap.value(v));
            qDebug() << "{{FORMAT}} :: "<< m_formatMap.value(v);
        }

        for(auto const &v : map.keys())
        {
            m_resultString = m_templateString.replace("_%"+v.toUpper()+"%_", map.value(v).toString());
        }

        qDebug() << "{TEMPLATE} :: "<< m_templateString;
        qDebug() << m_resultString;
        break;
    }

    case DocTypes::Reconciliaton: {
        break;
    }

    case DocTypes::Report: {
        m_defaultPrinterName = m_templatesObject.value("Report")
                .toObject().value("ReportPrinter")
                .toString();

        qDebug() << "{{DEFAULT_PRINTER_NAME}} :: "<< m_defaultPrinterName;

        QFile m_file(SystemConfig::getRootApplicationFolder()
                     +m_templatesObject.value("Report")
                     .toObject().value("ReportFile").toString());

        m_file.open(QIODevice::ReadOnly);
        m_templateString = QString(m_file.readAll());
        m_file.close();

        auto const map = m_dataObject.toVariantMap();

        for (auto const &v : m_formatMap.keys()) {
            m_templateString.replace("_%"+v.toUpper()+"%_", m_formatMap.value(v));
            qDebug() << "{{FORMAT}} :: "<< m_formatMap.value(v);
        }

        for(auto const &v : map.keys())
        {
            m_resultString = m_templateString.replace("_%"+v.toUpper()+"%_", map.value(v).toString());
        }

        qDebug() << "{TEMPLATE} :: "<< m_templateString;
        qDebug() << m_resultString;
        break;
    }

    case DocTypes::Statement: {
        break;
    }

    default: break;
    }

    return m_resultString;
}

const QStringList &NaiSysDocumentHandler::dataString() const
{return m_dataString;}

void NaiSysDocumentHandler::setDataString(const QStringList &newDataString)
{m_dataString = newDataString;}

const QString &NaiSysDocumentHandler::templateString() const
{return m_templateString;}

void NaiSysDocumentHandler::setTemplateString(const QString &newTemplateString)
{m_templateString = newTemplateString;}

const QString &NaiSysDocumentHandler::resultString() const
{return m_resultString;}

void NaiSysDocumentHandler::setResultString(const QString &newResultString)
{m_resultString = newResultString;}

const NaiSysDocumentHandler::DocumentStruct &NaiSysDocumentHandler::docStruct() const
{return m_docStruct;}

void NaiSysDocumentHandler::setDocStruct(const DocumentStruct &newDocStruct)
{m_docStruct = newDocStruct;}

const QJsonObject &NaiSysDocumentHandler::templatesObject() const
{return m_templatesObject;}

void NaiSysDocumentHandler::setTemplatesObject(const QJsonObject &newTemplatesObject)
{m_templatesObject = newTemplatesObject;}

const QJsonObject &NaiSysDocumentHandler::dataObject() const
{return m_dataObject;}

void NaiSysDocumentHandler::setDataObject(const QJsonObject &newDataObject)
{m_dataObject = newDataObject;}

const QMap<QString, QString> &NaiSysDocumentHandler::formatMap() const
{return m_formatMap;}

void NaiSysDocumentHandler::setFormatMap(const QMap<QString, QString> &newFormatMap)
{m_formatMap = newFormatMap;}

void NaiSysDocumentHandler::insertIntoFormatMap(const QString &key, const QString &value)
{m_formatMap.insert(key, value);}

const QString &NaiSysDocumentHandler::defaultPrinterName() const
{return m_defaultPrinterName;}

void NaiSysDocumentHandler::setDefaultPrinterName(const QString &newDefaultPrinterName)
{m_defaultPrinterName = newDefaultPrinterName;}

} // namespace NaiSys
