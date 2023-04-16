#ifndef NAISYSMENUSECTION_H
#define NAISYSMENUSECTION_H

#include <QObject>
#include <QQuickItem>

class NaiSysMenuSection : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(NaiSysMenuSection)
    QML_NAMED_ELEMENT(NaiSysMenuSection)
public:
    explicit NaiSysMenuSection(QObject *parent = nullptr);

    QString title() const;
    void setTitle(const QString &newTitle);
    void resetTitle();

signals:
    void titleChanged();

private:
    QString m_title;

    Q_PROPERTY(QString title READ title WRITE setTitle RESET resetTitle NOTIFY titleChanged)
};

#endif // NAISYSMENUSECTION_H
