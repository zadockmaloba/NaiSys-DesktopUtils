// ************************************************
// 2022, Zadock Maloba <zadockmaloba@outlook.com>
// ************************************************

import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15

Rectangle {
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
            Thx_Label {
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
                    Column {
                        anchors.fill: parent
                        spacing: root.form_field_spacing
                        Repeater {
                            id: fieldRepeater
                            model: form_data_model
                            delegate: Item {
                                id: fieldDelegate
                                //FIXME?: Find out why setting required properties affects other props
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
                                        Thx_Label {
                                            anchors.fill: parent
                                            text: model["name"]
                                        }
                                    }
                                    Rectangle {
                                        id: dataField
                                        width: parent.width * 0.6
                                        height: parent.height
                                        color: "grey"
                                        StackLayout {
                                            id: dataField_layout
                                            anchors.fill: parent
                                            currentIndex: {
                                                switch(model["type"]){
                                                case "input": return 0;
                                                case "combo": return 1;
                                                default: return 0;
                                                }
                                            }
                                            Thx_InputField {
                                                id: dataField_input
                                                echoMode: model["secure"] ? TextInput.Password : TextInput.Normal
                                                onTextChanged: {
                                                    //TODO: Remove debug lines
                                                    console.log(fieldDelegate.index);
                                                    form_data_model.set(fieldDelegate.index, {"value": dataField_input.text})
                                                }
                                            }
                                            Thx_ComboBox {
                                                id: dataField_combo
                                                //FIXME: Get ComboBox working in input form
                                                //Issue related to Arrays in ListModel as indicated by FIXME above
                                                //model: fieldRepeater.model["data"]
                                            }
                                        }
                                    }
                                }
                            }
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
                    Thx_Button {
                        id: root_footer_clearBtn
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        text: "Clear"
                        //TODO:Implement
                    }
                    Thx_Button {
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
}
