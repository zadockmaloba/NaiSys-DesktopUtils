#include "naisysformelement.h"

NaiSysFormElement::NaiSysFormElement()
{

}

QString NaiSysFormElement::label() const
{
    return m_label;
}

void NaiSysFormElement::setLabel(const QString &newLabel)
{
    if (m_label == newLabel)
        return;
    m_label = newLabel;
    emit labelChanged();
}

QVariant NaiSysFormElement::value() const
{
    return m_value;
}

void NaiSysFormElement::setValue(const QVariant &newValue)
{
    if (m_value == newValue)
        return;
    m_value = newValue;
    emit valueChanged();
}

NaiSysFormElement::FormElementType
NaiSysFormElement::type() const
{
    return m_type;
}

void NaiSysFormElement::setType(const FormElementType &newType)
{
    if (m_type == newType)
        return;
    m_type = newType;
    emit typeChanged();
}

bool NaiSysFormElement::masked() const
{
    return m_masked;
}

void NaiSysFormElement::setMasked(bool newMasked)
{
    if (m_masked == newMasked)
        return;
    m_masked = newMasked;
    emit maskedChanged();
}
