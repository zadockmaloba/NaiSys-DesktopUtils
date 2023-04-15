#ifndef NAISYSQUICKWINDOWEXSTENSION_H
#define NAISYSQUICKWINDOWEXSTENSION_H

#include <QQuickWindow>
#include <QMenuBar>
#include <QObject>
#include <QQuickItem>
#include <QVector>
#include <QSharedPointer>
#include <QScopedPointer>

#include <naisysmenu.h>

class NaiSysQuickWindowExstension : public QQuickWindow
{
    Q_OBJECT
    QML_NAMED_ELEMENT(NaiSysWindowPrivate)
    Q_DISABLE_COPY(NaiSysQuickWindowExstension)
    Q_PROPERTY(NaiSysMenu* menu READ menu WRITE setMenu NOTIFY menuChanged)
public:
    NaiSysQuickWindowExstension(QQuickWindow *parent = nullptr);

signals:
    void menuChanged();

public:
    NaiSysMenu* menu() const;
    void setMenu(NaiSysMenu *newMenu);

private:
    QScopedPointer<QMenuBar> m_menubar;
    NaiSysMenu* m_menu;

};

#endif // NAISYSQUICKWINDOWEXSTENSION_H
