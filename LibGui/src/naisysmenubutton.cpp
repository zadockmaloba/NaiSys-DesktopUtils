#include "naisysmenubutton.h"

NaiSysMenuButton::NaiSysMenuButton(QQuickItem *parent)
    : NaiSysMenuItem{parent}
{
    this->setType(MenuItemType::MenuButton);
}

QJSValue *NaiSysMenuButton::action() const
{
    return m_action;
}

void NaiSysMenuButton::setAction(QJSValue *newAction)
{
    if (m_action == newAction)
        return;
    m_action = newAction;
    emit actionChanged();
}
