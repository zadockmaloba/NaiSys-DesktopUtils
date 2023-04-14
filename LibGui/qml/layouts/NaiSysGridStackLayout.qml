import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.12

import "../components"

Item {
    id: root
    property string title: "Title"
    property string currentSource
    property int columnCount: 3
    property Component currentSourceComponent
    property ListModel mdl_pages: ListModel{
        ListElement{name: "page-1"; source: ""}
        ListElement{name: "page-2"; source: ""}
        ListElement{name: "page-3"; source: ""}
    }

    Column{
        id: root_layout
        anchors.fill: parent
        Item {
            id: root_header
            width: parent.width
            height: 50
            Rectangle{
                anchors.fill: parent
                opacity: 0.8
                color: "light grey"
                Button{
                    id: previousBtn
                    width: 30
                    height: 40
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    text: "<"
                    font.bold: true
                    font.pointSize: 12
                    visible: false
                    onClicked: {
                        root_body.replace(root_body_viewpanel, root_body_mainpanel);
                        previousBtn.visible = false;
                        title_text.text = root.title;
                    }
                }
                Text {
                    id: title_text
                    anchors.centerIn: parent
                    text: qsTr(root.title)
                    font.bold: true
                    font.pointSize: 12
                    font.family: "Arial"
                }
            }
        }
        StackView{
            id: root_body
            width: parent.width
            height: parent.height - root_header.height
            initialItem: root_body_mainpanel
            Component{
                id: root_body_mainpanel
                Grid{
                    id: root_body_mainpanel_layout
                    columns: root.columnCount
                    columnSpacing: 2
                    rowSpacing: 2
                    Repeater{
                        id: root_body_mainpanel_list
                        anchors.fill: parent
                        model: mdl_pages
                        delegate: ToolButton{
                            width: (parent.width / root.columnCount) - 2
                            height: parent.height * 0.4
                            text: model["name"]
                            onClicked: {
                                root.currentSource = model["source"];
                                model["sourceComponent"] ? root.currentSourceComponent = model["sourceComponent"] : console.log("");
                                root_body.replace(root_body_mainpanel, root_body_viewpanel);
                                title_text.text = root.title+" | "+model["name"]
                                previousBtn.visible = true;
                            }
                            Rectangle{
                                anchors.fill: parent
                                radius: 2
                                opacity: 0.95
                                color: "grey"
                            }
                        }
                    }
                }
            }
            Component{
                id: root_body_viewpanel

                Loader{
                    id: root_body_viewpanel_loader
                    Component.onCompleted: {
                        if(root.currentSource === ""){
                            root_body_viewpanel_loader.sourceComponent = root.currentSourceComponent;
                        }
                        else root_body_viewpanel_loader.setSource(root.currentSource);
                    }
                }
            }
        }
    }
}
