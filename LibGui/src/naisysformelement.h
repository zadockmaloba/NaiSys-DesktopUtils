#ifndef NAISYSFORMELEMENT_H
#define NAISYSFORMELEMENT_H

#include <QObject>
#include <QQuickItem>

class NaiSysFormElement : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(NaiSysFormElement)
public:
    enum class FormElementType{
        LineEdit,
        TextArea,
        ComboBox,
        CheckBOx,
        Toggle
    };
    Q_ENUM(FormElementType);

public:
    NaiSysFormElement();

    QString label() const;
    void setLabel(const QString &newLabel);

    QVariant value() const;
    void setValue(const QVariant &newValue);

    FormElementType type() const;
    void setType(const FormElementType &newType);

    bool masked() const;
    void setMasked(bool newMasked);

    QString displayRole() const;
    void setDisplayRole(const QString &newDisplayRole);

    bool editable() const;
    void setEditable(bool newEditable);

signals:
    void labelChanged();
    void valueChanged();
    void typeChanged();
    void maskedChanged();
    void displayRoleChanged();

    void editableChanged();

private:
    QString m_label;
    QString m_displayRole;
    QVariant m_value;
    FormElementType m_type;
    bool m_masked = false;
    bool m_editable = true;
    Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged)
    Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(FormElementType type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(bool masked READ masked WRITE setMasked NOTIFY maskedChanged)
    Q_PROPERTY(QString displayRole READ displayRole WRITE setDisplayRole NOTIFY displayRoleChanged)
    Q_PROPERTY(bool editable READ editable WRITE setEditable NOTIFY editableChanged)
};

#endif // NAISYSFORMELEMENT_H
