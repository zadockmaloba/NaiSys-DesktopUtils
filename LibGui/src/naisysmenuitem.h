#ifndef NAISYSMENUITEM_H
#define NAISYSMENUITEM_H

#include <QObject>
#include <QQuickItem>

class NaiSysMenuItem : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(NaiSysMenuItem)
    QML_NAMED_ELEMENT(NaiSysMenuItem)
public:
    explicit NaiSysMenuItem(QObject *parent = nullptr);

    QString title() const;
    void setTitle(const QString &newTitle);
    void resetTitle();

signals:

    void titleChanged();

private:
    QString m_title;

    Q_PROPERTY(QString title READ title WRITE setTitle RESET resetTitle NOTIFY titleChanged)
};

#endif // NAISYSMENUITEM_H
