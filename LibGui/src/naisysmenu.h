#ifndef NAISYSMENU_H
#define NAISYSMENU_H

#include <QObject>
#include <QQuickItem>
#include <QSharedPointer>
#include <naisysmenuitem.h>

class NaiSysMenu : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(NaiSysMenu)
    QML_NAMED_ELEMENT(NaiSysMenu)
    Q_CLASSINFO("DefaultProperty", "items")
    Q_PROPERTY(QQmlListProperty<NaiSysMenuItem> items READ items NOTIFY itemsChanged FINAL)
public:
    explicit NaiSysMenu(QObject *parent = nullptr);

    QQmlListProperty<NaiSysMenuItem> items();
    void appendItem(NaiSysMenuItem *);
    qsizetype itemCount() const;
    NaiSysMenuItem *item(qsizetype) const;
    void clearItems();
    void replaceItem(qsizetype, NaiSysMenuItem *);
    void removeLastItem();

signals:
    void itemsChanged();

private:
    static void appendItem(QQmlListProperty<NaiSysMenuItem> *list, NaiSysMenuItem *);
    static qsizetype itemCount(QQmlListProperty<NaiSysMenuItem> *);
    static NaiSysMenuItem *item(QQmlListProperty<NaiSysMenuItem> *, qsizetype);
    static void clearItems(QQmlListProperty<NaiSysMenuItem> *);
    static void replaceItem(QQmlListProperty<NaiSysMenuItem> *, qsizetype, NaiSysMenuItem *);
    static void removeLastItem(QQmlListProperty<NaiSysMenuItem> *);

private:
    QList<NaiSysMenuItem*> m_items;
};

#endif // NAISYSMENU_H
