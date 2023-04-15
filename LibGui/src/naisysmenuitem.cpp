#include "naisysmenuitem.h"

NaiSysMenuItem::NaiSysMenuItem(QObject *parent)
    : QObject{parent}
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

void NaiSysMenuItem::resetTitle()
{
    setTitle({}); // TODO: Adapt to use your actual default value
}
