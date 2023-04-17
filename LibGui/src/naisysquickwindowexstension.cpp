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
        auto _menu = newMenu->item(i);
        auto _section = m_menubar->addMenu(_menu->title());
        for(int j=0 ; j<(int)_menu->optionCount(); ++j) {
            auto _option = _menu->option(j);
            _section->addAction(_option->title());
        }
    }
    emit menuChanged();
}
