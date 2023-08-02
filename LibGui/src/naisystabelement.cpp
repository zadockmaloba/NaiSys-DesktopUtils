#include "naisystabelement.h"

NaiSysTabElement::NaiSysTabElement(QObject *parent)
    : QObject{parent},
    m_closable{false},
    m_editable{false},
    m_visible{true}
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

QObject *NaiSysTabElement::sourceComponent() const
{
    return m_sourceComponent;
}

void NaiSysTabElement::setSourceComponent(QObject *newSourceComponent)
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

bool NaiSysTabElement::visible() const
{
    return m_visible;
}

void NaiSysTabElement::setVisible(bool newVisible)
{
    if (m_visible == newVisible)
        return;
    m_visible = newVisible;
    emit visibleChanged();
}

bool NaiSysTabElement::editable() const
{
    return m_editable;
}

void NaiSysTabElement::setEditable(bool newEditable)
{
    if (m_editable == newEditable)
        return;
    m_editable = newEditable;
    emit editableChanged();
}
