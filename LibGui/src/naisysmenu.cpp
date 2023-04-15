#include "naisysmenu.h"

NaiSysMenu::NaiSysMenu(QObject *parent)
    : QObject{parent}
{

}

QQmlListProperty<NaiSysMenuItem> NaiSysMenu::items()
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

void NaiSysMenu::appendItem(NaiSysMenuItem *item)
{
    m_items.append(item);
    emit itemsChanged();
}

qsizetype NaiSysMenu::itemCount() const
{
    return m_items.count();
}

NaiSysMenuItem *NaiSysMenu::item(qsizetype index) const
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

void NaiSysMenu::replaceItem(qsizetype index, NaiSysMenuItem *item)
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

void NaiSysMenu::appendItem(QQmlListProperty<NaiSysMenuItem> *list, NaiSysMenuItem *item)
{
    static_cast<NaiSysMenu *>(list->data)->appendItem(item);
}

void NaiSysMenu::clearItems(QQmlListProperty<NaiSysMenuItem> *list)
{
    static_cast<NaiSysMenu *>(list->data)->clearItems();
}

void NaiSysMenu::replaceItem(QQmlListProperty<NaiSysMenuItem> *list, qsizetype index, NaiSysMenuItem *item)
{
    static_cast<NaiSysMenu *>(list->data)->replaceItem(index, item);
}

void NaiSysMenu::removeLastItem(QQmlListProperty<NaiSysMenuItem> *list)
{
    static_cast<NaiSysMenu *>(list->data)->removeLastItem();
}

NaiSysMenuItem *NaiSysMenu::item(QQmlListProperty<NaiSysMenuItem> *list, qsizetype index)
{
    return static_cast<NaiSysMenu *>(list->data)->item(index);
}

qsizetype NaiSysMenu::itemCount(QQmlListProperty<NaiSysMenuItem> *list)
{
    return static_cast<NaiSysMenu *>(list->data)->itemCount();
}
