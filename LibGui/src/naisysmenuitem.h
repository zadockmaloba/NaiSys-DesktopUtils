#ifndef NAISYSMENUITEM_H
#define NAISYSMENUITEM_H

#include <QObject>
#include <QQuickItem>

class NaiSysMenuItem : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("NaiSysMenuItem is an abstract base class. Use either NaiSysMenuButton or NaiSysSubMenu")
public:
    enum class MenuItemType {
        MenuButton,
        SubMenu
    };
    Q_ENUM(MenuItemType)

public:
    explicit NaiSysMenuItem(QQuickItem *parent = nullptr);

    QString title() const;
    void setTitle(const QString &newTitle);

    MenuItemType type() const;
    void setType(MenuItemType newType);

signals:

    void titleChanged();

    void typeChanged();

private:
    QString m_title;
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)

    MenuItemType m_type;
    Q_PROPERTY(MenuItemType type READ type WRITE setType NOTIFY typeChanged)
};

#endif // NAISYSMENUITEM_H
