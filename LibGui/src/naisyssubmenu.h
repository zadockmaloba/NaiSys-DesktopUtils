#ifndef NAISYSSUBMENU_H
#define NAISYSSUBMENU_H

#include "naisysmenuitem.h"
#include <QObject>
#include <QQuickItem>

class NaiSysSubMenu : public NaiSysMenuItem
{
    Q_OBJECT
    QML_NAMED_ELEMENT(NaiSysSubMenu)
public:
    explicit NaiSysSubMenu(QQuickItem *parent = nullptr);
};

#endif // NAISYSSUBMENU_H
