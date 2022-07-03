#ifndef NAISYS_NAISYSDOCUMENTHANDLER_H
#define NAISYS_NAISYSDOCUMENTHANDLER_H

#include "NaiSys_DesktopUtils_global.h"

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>

#include <QFile>
#include <QMap>

#include "systemconfig.h"

namespace NaiSys {

class NAISYSDESKTOPUTILS_EXPORT NaiSysDocumentHandler
{
    enum DocTypes{
        Receipt,
        Reconciliaton,
        Report,
        Statement
    };

    struct DocumentStruct{
        int _template_handle;
        QStringList _data_string;
    };

public: //static methods
    static const QStringList jsonValsToStringList(const QJsonObject &obj);
    static const QString jsonValsToHtmlTable(const QJsonArray &jarr);

public:
    NaiSysDocumentHandler();
    explicit NaiSysDocumentHandler(const QStringList &datString);
    explicit NaiSysDocumentHandler(const DocumentStruct &docStruct);
    NaiSysDocumentHandler(const QJsonObject &datObject, int templateHandle = 0);
    NaiSysDocumentHandler(const QStringList &datString, int templateHandle = 0);

    const QString &renderDocument();

    const QStringList &dataString() const;
    void setDataString(const QStringList &newDataString);
    const QString &templateString() const;
    void setTemplateString(const QString &newTemplateString);
    const QString &resultString() const;
    void setResultString(const QString &newResultString);
    const DocumentStruct &docStruct() const;
    void setDocStruct(const DocumentStruct &newDocStruct);
    const QJsonObject &templatesObject() const;
    void setTemplatesObject(const QJsonObject &newTemplatesObject);
    const QJsonObject &dataObject() const;
    void setDataObject(const QJsonObject &newDataObject);

    const QMap<QString, QString> &formatMap() const;
    Q_INVOKABLE void setFormatMap(const QMap<QString, QString> &newFormatMap);
    Q_INVOKABLE void insertIntoFormatMap(const QString &key, const QString &value);

    const QString &defaultPrinterName() const;
    void setDefaultPrinterName(const QString &newDefaultPrinterName);

private://methods

signals:

private: //members
    QStringList m_dataString;
    QString m_templateString, m_resultString, m_defaultPrinterName;
    DocumentStruct m_docStruct;
    QJsonObject m_templatesObject, m_dataObject;
    QMap <QString , QString>m_formatMap;
    int m_templateHandle;
};

} // namespace NaiSys

#endif // NAISYS_NAISYSDOCUMENTHANDLER_H
