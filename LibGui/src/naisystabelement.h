#ifndef NAISYSTABELEMENT_H
#define NAISYSTABELEMENT_H

#include <QObject>
#include <QQuickItem>
#include <QQuickPaintedItem>

class NaiSysTabElement : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(NaiSysTabElement)
public:
    enum class SourceType {
        FILE,
        COMPONENT
    };
    Q_ENUM(SourceType)
public:
    explicit NaiSysTabElement(QObject *parent = nullptr);

    QString title() const;
    void setTitle(const QString &newTitle);

    QString source() const;
    void setSource(const QString &newSource);

    QObject *sourceComponent() const;
    void setSourceComponent(QObject *newSourceComponent);

    bool closable() const;
    void setClosable(bool newClosable);

    bool visible() const;
    void setVisible(bool newVisible);

    bool editable() const;
    void setEditable(bool newEditable);

signals:
    void titleChanged();
    void sourceChanged();
    void sourceComponentChanged();
    void closableChanged();
    void visibleChanged();
    void editableChanged();

private:
    QString m_title;
    QString m_source;
    QObject *m_sourceComponent;
    bool m_closable;
    bool m_visible;
    bool m_editable;

    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QObject *sourceComponent READ sourceComponent WRITE setSourceComponent NOTIFY sourceComponentChanged)
    Q_PROPERTY(bool closable READ closable WRITE setClosable NOTIFY closableChanged)
    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(bool editable READ editable WRITE setEditable NOTIFY editableChanged)
};

#endif // NAISYSTABELEMENT_H
