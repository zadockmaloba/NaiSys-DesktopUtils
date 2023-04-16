#include "naisysmenusection.h"

NaiSysMenuSection::NaiSysMenuSection(QObject *parent)
    : QObject{parent}
{

}

QString NaiSysMenuSection::title() const
{
    return m_title;
}

void NaiSysMenuSection::setTitle(const QString &newTitle)
{
    if (m_title == newTitle)
        return;
    m_title = newTitle;
    emit titleChanged();
}

void NaiSysMenuSection::resetTitle()
{
    setTitle({}); // TODO: Adapt to use your actual default value
}
