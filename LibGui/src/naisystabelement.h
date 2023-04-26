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

    QQuickPaintedItem *sourceComponent() const;
    void setSourceComponent(QQuickPaintedItem *newSourceComponent);

    bool closable() const;
    void setClosable(bool newClosable);

signals:
    void titleChanged();
    void sourceChanged();
    void sourceComponentChanged();
    void closableChanged();

private:
    QString m_title;
    QString m_source;
    QQuickPaintedItem *m_sourceComponent;
    bool m_closable;

    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QQuickPaintedItem *sourceComponent READ sourceComponent WRITE setSourceComponent NOTIFY sourceComponentChanged)
    Q_PROPERTY(bool closable READ closable WRITE setClosable NOTIFY closableChanged)
};

#endif // NAISYSTABELEMENT_H
