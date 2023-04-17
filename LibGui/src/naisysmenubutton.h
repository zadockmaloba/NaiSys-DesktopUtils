#ifndef NAISYSMENUBUTTON_H
#define NAISYSMENUBUTTON_H

#include "naisysmenuitem.h"
#include <QObject>
#include <QQuickItem>
#include <QJSValue>
#include <QJSValueList>

class NaiSysMenuButton : public NaiSysMenuItem
{
    Q_OBJECT
    QML_NAMED_ELEMENT(NaiSysMenuAction)
public:
    explicit NaiSysMenuButton(QQuickItem *parent = nullptr);

    QJSValue *action() const;
    void setAction(QJSValue *newAction);

signals:
    void actionChanged();

private:
    QJSValue *m_action = nullptr;
    Q_PROPERTY(QJSValue *action READ action WRITE setAction NOTIFY actionChanged)
};

#endif // NAISYSMENUBUTTON_H
