// ************************************************
// 2022, Zadock Maloba <zadockmaloba@outlook.com>
// ************************************************

import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

NaiSysDiv {
    id: root
    property bool form_title_show: true
    property double form_opacity_value: 0.8
    property int form_field_height: 28
    property int form_field_spacing: 4
    property string form_acceptbtn_title: "Submit"
    property string form_accent_color: "light grey"
    property string form_title_text: "Title"
    //FIXME: Find a way to include arrays into a ListModel
    property ListModel form_data_model: ListModel {
        ListElement{name:"Test1"; type:"input"; secure: false; data:[]}
        ListElement{name:"Test2"; type:"input"; secure: true; data:[]}
        ListElement{name:"Test3"; type:"combo"; secure: false; data:[]}
    }
    signal dataSubmitted()

    opacity: form_opacity_value
    color: form_accent_color

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
                text_size: "h3"
            }
        }
        Column{
            id: root_body_layout
            width: parent.width
            height: parent.height * 0.8
            spacing: root.form_field_spacing
            Item {
                id: root_body
                width: parent.width
                height: parent.height - root_footer.height
                ScrollView{
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
                        onClicked: root.dataSubmitted()
                    }
                }
            }
        }
    }

    component FormDelegate : Item {
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
                        switch(model.type){
                        case NaiSysFormElement.LineEdit: return comp_LineEdit;
                        case NaiSysFormElement.ComboBox: return comp_ComboBox;
                        default: return NaiSysFormElement.LineEdit;
                        }
                    }
                    Component  {
                        id: comp_LineEdit
                        NaiSysInputField {
                            id: dataField_input
                            echoMode: model.masked ? TextInput.Password : TextInput.Normal
                            text: model.value
                            onTextChanged: {
                            }
                        }
                    }
                    Component {
                        id: comp_ComboBox
                        NaiSysComboBox {
                            id: dataField_combo
                            model: form_model.elements[index].value
                        }
                    }
                }
            }
        }
    }
}
