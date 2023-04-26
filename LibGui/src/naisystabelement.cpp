#include "naisystabelement.h"

NaiSysTabElement::NaiSysTabElement(QObject *parent)
    : QObject{parent}
{

}

QString NaiSysTabElement::title() const
{
    return m_title;
}

void NaiSysTabElement::setTitle(const QString &newTitle)
{
    if (m_title == newTitle)
        return;
    m_title = newTitle;
    emit titleChanged();
}

QString NaiSysTabElement::source() const
{
    return m_source;
}

void NaiSysTabElement::setSource(const QString &newSource)
{
    if (m_source == newSource)
        return;
    m_source = newSource;
    emit sourceChanged();
}

QQuickPaintedItem *NaiSysTabElement::sourceComponent() const
{
    return m_sourceComponent;
}

void NaiSysTabElement::setSourceComponent(QQuickPaintedItem *newSourceComponent)
{
    if (m_sourceComponent == newSourceComponent)
        return;
    m_sourceComponent = newSourceComponent;
    emit sourceComponentChanged();
}

bool NaiSysTabElement::closable() const
{
    return m_closable;
}

void NaiSysTabElement::setClosable(bool newClosable)
{
    if (m_closable == newClosable)
        return;
    m_closable = newClosable;
    emit closableChanged();
}
