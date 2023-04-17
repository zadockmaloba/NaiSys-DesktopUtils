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

QQmlListProperty<NaiSysMenuItem> NaiSysMenuSection::options()
{
    return { this,
             this,
             &NaiSysMenuSection::appendOption,
             &NaiSysMenuSection::optionCount,
             &NaiSysMenuSection::option,
             &NaiSysMenuSection::clearOptions,
             &NaiSysMenuSection::replaceOption,
             &NaiSysMenuSection::removeLastOption };
}

void NaiSysMenuSection::appendOption(NaiSysMenuItem *option)
{
    m_options.append(option);
    emit optionsChanged();
}

qsizetype NaiSysMenuSection::optionCount() const
{
    return m_options.count();
}

NaiSysMenuItem *NaiSysMenuSection::option(qsizetype index) const
{
    return m_options.at(index);
}

void NaiSysMenuSection::clearOptions()
{
    if (!m_options.empty()) {
        m_options.clear();
        emit optionsChanged();
    }
}

void NaiSysMenuSection::replaceOption(qsizetype index, NaiSysMenuItem *option)
{
    if (m_options.size() > index) {
        m_options[index] = option;
        emit optionsChanged();
    }
}

void NaiSysMenuSection::removeLastOption()
{
    if (!m_options.empty()) {
        m_options.removeLast();
        emit optionsChanged();
    }
}

void NaiSysMenuSection::appendOption(QQmlListProperty<NaiSysMenuItem> *list, NaiSysMenuItem *option)
{
    static_cast<NaiSysMenuSection *>(list->data)->appendOption(option);
}

qsizetype NaiSysMenuSection::optionCount(QQmlListProperty<NaiSysMenuItem> *list)
{
    return static_cast<NaiSysMenuSection *>(list->data)->optionCount();
}

NaiSysMenuItem *NaiSysMenuSection::option(QQmlListProperty<NaiSysMenuItem> *list, qsizetype index)
{
    return static_cast<NaiSysMenuSection *>(list->data)->option(index);
}

void NaiSysMenuSection::clearOptions(QQmlListProperty<NaiSysMenuItem> *list)
{
    static_cast<NaiSysMenuSection *>(list->data)->clearOptions();
}

void NaiSysMenuSection::replaceOption(QQmlListProperty<NaiSysMenuItem> *list, qsizetype index, NaiSysMenuItem *option)
{
    static_cast<NaiSysMenuSection *>(list->data)->replaceOption(index, option);
}

void NaiSysMenuSection::removeLastOption(QQmlListProperty<NaiSysMenuItem> *list)
{
    static_cast<NaiSysMenuSection *>(list->data)->removeLastOption();
}
