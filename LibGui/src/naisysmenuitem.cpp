#include "naisysmenuitem.h"

NaiSysMenuItem::NaiSysMenuItem(QQuickItem *parent)
    : QQuickItem{parent}
{

}

QString NaiSysMenuItem::title() const
{
    return m_title;
}

void NaiSysMenuItem::setTitle(const QString &newTitle)
{
    if (m_title == newTitle)
        return;
    m_title = newTitle;
    emit titleChanged();
}

NaiSysMenuItem::MenuItemType NaiSysMenuItem::type() const
{
    return m_type;
}

void NaiSysMenuItem::setType(MenuItemType newType)
{
    if (m_type == newType)
        return;
    m_type = newType;
    emit typeChanged();
}
