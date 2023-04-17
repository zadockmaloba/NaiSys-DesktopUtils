#ifndef NAISYSMENUSECTION_H
#define NAISYSMENUSECTION_H

#include <QObject>
#include <QQuickItem>
#include "naisysmenuitem.h"

class NaiSysMenuSection : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(NaiSysMenuSection)
    QML_NAMED_ELEMENT(NaiSysMenuSection)
    Q_CLASSINFO("DefaultProperty", "options")
    Q_PROPERTY(QQmlListProperty<NaiSysMenuItem> options READ options NOTIFY optionsChanged FINAL)
public:
    explicit NaiSysMenuSection(QObject *parent = nullptr);

    QString title() const;
    void setTitle(const QString &newTitle);
    void resetTitle();

    QQmlListProperty<NaiSysMenuItem> options();
    void appendOption(NaiSysMenuItem *);
    qsizetype optionCount() const;
    NaiSysMenuItem *option(qsizetype) const;
    void clearOptions();
    void replaceOption(qsizetype, NaiSysMenuItem *);
    void removeLastOption();

signals:
    void titleChanged();
    void optionsChanged();

private:
    static void appendOption(QQmlListProperty<NaiSysMenuItem> *list, NaiSysMenuItem *);
    static qsizetype optionCount(QQmlListProperty<NaiSysMenuItem> *);
    static NaiSysMenuItem *option(QQmlListProperty<NaiSysMenuItem> *, qsizetype);
    static void clearOptions(QQmlListProperty<NaiSysMenuItem> *);
    static void replaceOption(QQmlListProperty<NaiSysMenuItem> *, qsizetype, NaiSysMenuItem *);
    static void removeLastOption(QQmlListProperty<NaiSysMenuItem> *);

private:
    QString m_title;
    Q_PROPERTY(QString title READ title WRITE setTitle RESET resetTitle NOTIFY titleChanged)
    QList<NaiSysMenuItem*> m_options;
};

#endif // NAISYSMENUSECTION_H
