#ifndef NAISYSMENU_H
#define NAISYSMENU_H

#include <QObject>
#include <QQuickItem>
#include <QSharedPointer>
#include <naisysmenusection.h>

class NaiSysMenu : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(NaiSysMenu)
    QML_NAMED_ELEMENT(NaiSysMenu)
    Q_CLASSINFO("DefaultProperty", "items")
    Q_PROPERTY(QQmlListProperty<NaiSysMenuSection> items READ items NOTIFY itemsChanged FINAL)
public:
    explicit NaiSysMenu(QObject *parent = nullptr);

    QQmlListProperty<NaiSysMenuSection> items();
    void appendItem(NaiSysMenuSection *);
    qsizetype itemCount() const;
    NaiSysMenuSection *item(qsizetype) const;
    void clearItems();
    void replaceItem(qsizetype, NaiSysMenuSection *);
    void removeLastItem();

signals:
    void itemsChanged();

private:
    static void appendItem(QQmlListProperty<NaiSysMenuSection> *list, NaiSysMenuSection *);
    static qsizetype itemCount(QQmlListProperty<NaiSysMenuSection> *);
    static NaiSysMenuSection *item(QQmlListProperty<NaiSysMenuSection> *, qsizetype);
    static void clearItems(QQmlListProperty<NaiSysMenuSection> *);
    static void replaceItem(QQmlListProperty<NaiSysMenuSection> *, qsizetype, NaiSysMenuSection *);
    static void removeLastItem(QQmlListProperty<NaiSysMenuSection> *);

private:
    QList<NaiSysMenuSection*> m_items;
};

#endif // NAISYSMENU_H
