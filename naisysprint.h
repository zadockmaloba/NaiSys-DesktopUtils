#ifndef NAISYSPRINT_H
#define NAISYSPRINT_H

#include "NaiSys_DesktopUtils_global.h"

#include <QObject>
#include <QFile>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintEngine>
#include <QtPrintSupport/QPrinterInfo>
#include <QPainter>
#include <QPaintEngine>
#include <QTextDocument>
#include <QTextCursor>

#include "naisysjsonobject.h"
#include "naisysdocumenthandler.h"
#include "systemconfig.h"

class NAISYSDESKTOPUTILS_EXPORT NaiSysPrint : public QObject
{
    Q_OBJECT
public:
    enum PrintEnum{
        Receipt,
        Statement,
        QuerryResult
    };
public:
    explicit NaiSysPrint(QObject *parent = nullptr);

    void addPrinter(QWidget* parent = nullptr);
    void configurePrinter(const QPrinter* _prntr, QWidget* parent = nullptr);

    void printDocument(const QString& printData);
    QString fillDocumentData(const QByteArray& _data, QString _docTemplate);

    const QList<QPrinterInfo> &availablePrinters() const;
    void setAvailablePrinters(const QList<QPrinterInfo> &newAvailablePrinters);

    QPrinterInfo selectedPrinterInfo() const;
    void setSelectedPrinterInfo(QPrinterInfo newSelectedPrinterInfo);

    Q_INVOKABLE bool printJsonDocument(const QJsonObject &obj, int docHandle = 0, const QJsonObject &format = QJsonObject());
    Q_INVOKABLE QString jsonToHtmlTable(const QJsonArray &jarr);
    Q_INVOKABLE QJsonArray json_availablePrinters();
    Q_INVOKABLE QJsonObject json_printerInfo(const QString &printername);

signals:

private:
    QPrinter *current_printer;
    QString current_printer_name;
    QPrinterInfo m_selectedPrinterInfo;
    QList <QPrinterInfo> m_availablePrinters;
};

#endif // NAISYSPRINT_H
