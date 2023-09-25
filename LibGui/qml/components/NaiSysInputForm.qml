// ************************************************
// 2022, Zadock Maloba <zadockmaloba@outlook.com>
// ************************************************
import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import libgui

NaiSysDiv {
    id: root
    default property NaiSysFormModel form_model: NaiSysFormModel {
        NaiSysFormElement {
            label: "Default"
            type: NaiSysFormElement.LineEdit
            value: "Testing"
        }
        NaiSysFormElement {
            label: "Default 2"
            type: NaiSysFormElement.LineEdit
            value: "Testing"
        }
    }
    property bool form_title_show: true
    property double form_opacity_value: 0.8
    property int form_field_height: 28
    property int form_field_spacing: 4
    property string form_acceptbtn_title: "Submit"
    property string form_accent_color: "light grey"
    property string form_title_text: "Title"
    signal dataSubmitted(var data)

    opacity: form_opacity_value
    color: form_accent_color

    function get_form_data() {
        var ret = {}
        for (var i in form_model.elements) {
            var _lbl = form_model.elements[i].label
            var _val = form_model.elements[i].value
            ret[_lbl] = _val
        }
        return ret
    }

    Column {
        id: root_layout
        anchors.fill: parent
        anchors.topMargin: 4
        anchors.bottomMargin: 4
        anchors.leftMargin: 4
        anchors.rightMargin: 4
        Item {
            id: root_header
            width: parent.width
            height: parent.height * 0.2
            NaiSysLabel {
                id: root_header_label
                anchors.fill: parent
                text: root.form_title_text
                font.pixelSize: 26
                font.bold: true
            }
        }
        Column {
            id: root_body_layout
            width: parent.width
            height: parent.height * 0.8
            spacing: root.form_field_spacing
            Item {
                id: root_body
                width: parent.width
                height: parent.height - root_footer.height
                Item {
                    anchors.fill: parent
                    visible: true
                    Column {
                        anchors.fill: parent
                        spacing: root.form_field_spacing
                        Repeater {
                            id: fieldRepeater
                            model: form_model.elements
                            delegate: FormDelegate {}
                        }
                    }
                }
            }
            Item {
                id: root_footer
                width: parent.width
                height: root.form_field_height * 2
                RowLayout {
                    id: root_footer_layout
                    anchors.fill: parent
                    anchors.topMargin: 5
                    anchors.bottomMargin: 10
                    anchors.leftMargin: 5
                    anchors.rightMargin: 5
                    spacing: 10
                    NaiSysButton {
                        id: root_footer_clearBtn
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        text: "Clear"
                        //TODO:Implement
                    }
                    NaiSysButton {
                        id: root_footer_acceptBtn
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        text: root.form_acceptbtn_title
                        onClicked: root.dataSubmitted(root.get_form_data())
                    }
                }
            }
        }
    }

    component FormDelegate: Item {
        required property int index
        required property QtObject model
        width: parent.width
        height: root.form_field_height
        Row {
            id: fieldDelegate_layout
            anchors.fill: parent
            Rectangle {
                id: labelField
                width: parent.width * 0.4
                height: parent.height
                NaiSysLabel {
                    anchors.fill: parent
                    text: model.label
                }
            }
            Rectangle {
                id: dataField
                width: parent.width * 0.6
                height: parent.height
                color: "grey"
                Loader {
                    id: dataField_layout
                    anchors.fill: parent
                    enabled: model.editable
                    sourceComponent: {
                        switch (model.type) {
                        case NaiSysFormElement.LineEdit:
                            return comp_LineEdit
                        case NaiSysFormElement.ComboBox:
                            return comp_ComboBox
                        default:
                            return NaiSysFormElement.LineEdit
                        }
                    }
                    Component {
                        id: comp_LineEdit
                        NaiSysInputField {
                            id: dataField_input
                            echoMode: model.masked ? TextInput.Password : TextInput.Normal
                            text: model.value
                            readOnly: !model.editable
                            onTextChanged: {
                                model.value = text
                            }
                        }
                    }
                    Component {
                        id: comp_ComboBox
                        NaiSysComboBox {
                            id: dataField_combo
                            editable: form_model.elements[index].editable
                            model: form_model.elements[index].value
                        }
                    }
                    Component {
                        id: comp_CheckBox
                        CheckBox {
                            id: dataField_check
                            checkable: model.editable
                            checkState: model.value ? Qt.Checked : Qt.Unchecked
                        }
                    }
                }
            }
        }
    }
}
