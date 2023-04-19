#include "naisyssubmenu.h"

NaiSysSubMenu::NaiSysSubMenu(QQuickItem *parent)
    : NaiSysMenuItem{parent}
{
    this->setType(MenuItemType::SubMenu);
}
