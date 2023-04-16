#include "naisysmenu.h"

NaiSysMenu::NaiSysMenu(QObject *parent)
    : QObject{parent}
{

}

QQmlListProperty<NaiSysMenuSection> NaiSysMenu::items()
{
    return { this,
             this,
             &NaiSysMenu::appendItem,
             &NaiSysMenu::itemCount,
             &NaiSysMenu::item,
             &NaiSysMenu::clearItems,
             &NaiSysMenu::replaceItem,
             &NaiSysMenu::removeLastItem };
}

void NaiSysMenu::appendItem(NaiSysMenuSection *item)
{
    m_items.append(item);
    emit itemsChanged();
}

qsizetype NaiSysMenu::itemCount() const
{
    return m_items.count();
}

NaiSysMenuSection *NaiSysMenu::item(qsizetype index) const
{
    return m_items.at(index);
}

void NaiSysMenu::clearItems()
{
    if (!m_items.empty()) {
        m_items.clear();
        emit itemsChanged();
    }
}

void NaiSysMenu::replaceItem(qsizetype index, NaiSysMenuSection *item)
{
    if (m_items.size() > index) {
        m_items[index] = item;
        emit itemsChanged();
    }
}

void NaiSysMenu::removeLastItem()
{
    if (!m_items.empty()) {
        m_items.removeLast();
        emit itemsChanged();
    }
}

void NaiSysMenu::appendItem(QQmlListProperty<NaiSysMenuSection> *list, NaiSysMenuSection *item)
{
    static_cast<NaiSysMenu *>(list->data)->appendItem(item);
}

void NaiSysMenu::clearItems(QQmlListProperty<NaiSysMenuSection> *list)
{
    static_cast<NaiSysMenu *>(list->data)->clearItems();
}

void NaiSysMenu::replaceItem(QQmlListProperty<NaiSysMenuSection> *list, qsizetype index, NaiSysMenuSection *item)
{
    static_cast<NaiSysMenu *>(list->data)->replaceItem(index, item);
}

void NaiSysMenu::removeLastItem(QQmlListProperty<NaiSysMenuSection> *list)
{
    static_cast<NaiSysMenu *>(list->data)->removeLastItem();
}

NaiSysMenuSection *NaiSysMenu::item(QQmlListProperty<NaiSysMenuSection> *list, qsizetype index)
{
    return static_cast<NaiSysMenu *>(list->data)->item(index);
}

qsizetype NaiSysMenu::itemCount(QQmlListProperty<NaiSysMenuSection> *list)
{
    return static_cast<NaiSysMenu *>(list->data)->itemCount();
}
