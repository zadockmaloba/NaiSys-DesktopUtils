#include "naisysquickwindowexstension.h"

NaiSysQuickWindowExstension::NaiSysQuickWindowExstension(QQuickWindow *parent)
    : QQuickWindow{parent},
      m_menubar{new QMenuBar}
{

}

NaiSysMenu* NaiSysQuickWindowExstension::menu() const
{
    return m_menu;
}

void NaiSysQuickWindowExstension::setMenu(NaiSysMenu* newMenu)
{
    m_menu = newMenu;
    for(int i=0 ; i<(int)newMenu->itemCount(); ++i) {
        auto fileMenu = m_menubar->addMenu(newMenu->item(i)->title());
        fileMenu->addAction("1");
        fileMenu->addAction("2");
        fileMenu->addAction("3");
        fileMenu->addMenu("Submenu");
    }
    emit menuChanged();
}
