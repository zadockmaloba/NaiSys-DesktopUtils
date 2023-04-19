#include "naisysformmodel.h"

NaiSysFormModel::NaiSysFormModel()
{

}

QQmlListProperty<NaiSysFormElement> NaiSysFormModel::elements()
{
    return { this,
             this,
             &NaiSysFormModel::appendElement,
             &NaiSysFormModel::elementCount,
             &NaiSysFormModel::element,
             &NaiSysFormModel::clearElements,
             &NaiSysFormModel::replaceElement,
             &NaiSysFormModel::removeLastElement };
}

void NaiSysFormModel::appendElement(NaiSysFormElement *element)
{
    m_elements.append(element);
    emit elementsChanged();
}

qsizetype NaiSysFormModel::elementCount() const
{
    return m_elements.count();
}

NaiSysFormElement *NaiSysFormModel::element(qsizetype index) const
{
    return m_elements.at(index);
}

void NaiSysFormModel::clearElements()
{
    if (!m_elements.empty()) {
        m_elements.clear();
        emit elementsChanged();
    }
}

void NaiSysFormModel::replaceElement(qsizetype index, NaiSysFormElement *element)
{
    if (m_elements.size() > index) {
        m_elements[index] = element;
        emit elementsChanged();
    }
}

void NaiSysFormModel::removeLastElement()
{
    if (!m_elements.empty()) {
        m_elements.removeLast();
        emit elementsChanged();
    }
}

void NaiSysFormModel::appendElement(QQmlListProperty<NaiSysFormElement> *list, NaiSysFormElement *element)
{
    static_cast<NaiSysFormModel *>(list->data)->appendElement(element);
}

qsizetype NaiSysFormModel::elementCount(QQmlListProperty<NaiSysFormElement> *list)
{
    return static_cast<NaiSysFormModel *>(list->data)->elementCount();
}

NaiSysFormElement *NaiSysFormModel::element(QQmlListProperty<NaiSysFormElement> *list, qsizetype index)
{
    return static_cast<NaiSysFormModel *>(list->data)->element(index);
}

void NaiSysFormModel::clearElements(QQmlListProperty<NaiSysFormElement> *list)
{
    static_cast<NaiSysFormModel *>(list->data)->clearElements();
}

void NaiSysFormModel::replaceElement(QQmlListProperty<NaiSysFormElement> *list, qsizetype index, NaiSysFormElement *element)
{
    static_cast<NaiSysFormModel *>(list->data)->replaceElement(index, element);
}

void NaiSysFormModel::removeLastElement(QQmlListProperty<NaiSysFormElement> *list)
{
    static_cast<NaiSysFormModel *>(list->data)->removeLastElement();
}
