#ifndef NAISYSFORMMODEL_H
#define NAISYSFORMMODEL_H

#include <QObject>
#include <QQuickItem>
#include "naisysformelement.h"

class NaiSysFormModel : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(NaiSysFormModel)
    Q_CLASSINFO("DefaultProperty", "elements")
    Q_PROPERTY(QQmlListProperty<NaiSysFormElement> elements READ elements NOTIFY elementsChanged)
public:
    NaiSysFormModel();

    QQmlListProperty<NaiSysFormElement> elements();
    void appendElement(NaiSysFormElement *);
    qsizetype elementCount() const;
    NaiSysFormElement *element(qsizetype) const;
    void clearElements();
    void replaceElement(qsizetype, NaiSysFormElement *);
    void removeLastElement();

signals:
    void elementsChanged();

private:
    static void appendElement(QQmlListProperty<NaiSysFormElement> *list, NaiSysFormElement *);
    static qsizetype elementCount(QQmlListProperty<NaiSysFormElement> *);
    static NaiSysFormElement *element(QQmlListProperty<NaiSysFormElement> *, qsizetype);
    static void clearElements(QQmlListProperty<NaiSysFormElement> *);
    static void replaceElement(QQmlListProperty<NaiSysFormElement> *, qsizetype, NaiSysFormElement *);
    static void removeLastElement(QQmlListProperty<NaiSysFormElement> *);

private:
    QList<NaiSysFormElement*> m_elements;
};

#endif // NAISYSFORMMODEL_H
