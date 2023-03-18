// ************************************************
// 2022, Zadock Maloba <zadockmaloba@outlook.com>
// ************************************************

import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root

    property int tab_bar_height: 35
    property int tab_button_width: 120
    property bool tab_init_all: false
    property Component tab_default_view
    property string tab_default_view_name: "Home"
    property string tab_bar_color: "light grey"
    property string tab_button_color: "light grey"
    property ListModel tab_items: ListModel {
        ListElement {name:"Home"; closable: false; source: ""}
    }

    function newTab(m_name, m_source){
        bufferModel.append({name: m_name, source: m_source});
    }
    function newTabComponent(m_name, m_source){
        bufferModel.append({name: m_name, source: "", sourceComponent: m_source});
    }
    function removeTab(m_index) {
        bufferModel.remove(m_index);
    }

    ListModel {id: bufferModel}
    Thx_MenuWidget {
        id: contextMenu
        x: addTabButton.x
        y: addTabButton.y + addTabButton.height
        Repeater{
            model: root.tab_items
            delegate: MenuItem {
                text: model["name"]
                onClicked: {
                    root.newTab(text, model["source"]);
                }
            }
        }
    }

    Component.onCompleted: {
        if(!root.tab_default_view){
            if(root.initAll){
                for(var i=0; i<root.tab_items.count;++i){
                    bufferModel.append(root.tab_items.get(i));
                }
            }
            else bufferModel.append(root.tab_items.get(0));
        }
        else{
            bufferModel.append({name: root.tab_default_view_name,
                                source: "",
                                sourceComponent: root.tab_default_view});
        }
    }

    Column {
        id: root_layout
        anchors.fill: parent
        Rectangle {
            id: root_header
            height: root.tab_bar_height
            width: parent.width
            color: "light gray"
            ScrollView {
                anchors.fill: parent
                anchors.leftMargin: 2
                anchors.rightMargin: 2
                anchors.bottomMargin: 2
                anchors.topMargin: 2
                Row {
                    id: root_header_layout
                    anchors.fill: parent
                    Repeater {
                        model: bufferModel
                        delegate: ToolButton {
                            height: parent.height
                            width: 120
                            text: model["name"]
                            font.bold: true
                            onClicked: {
                                root_body_stack.currentIndex = index;
                            }
                            background: Rectangle {
                                radius: 2
                                opacity: 0.7
                                border.color: "white"
                                color: index === root_body_stack.currentIndex ? "grey" : "light grey"
                                gradient: Gradient{
                                    GradientStop{position: 0; color: "light grey"}
                                    GradientStop{
                                        position: 1;
                                        color: index === root_body_stack.currentIndex ?
                                                   "grey" : "light grey"
                                    }
                                }
                            }
                        }
                    }
                    Button{
                        id: addTabButton
                        height: parent.height
                        width: 40
                        enabled: !root.tab_init_all
                        text: "+"
                        onClicked: {
                            contextMenu.open();
                        }
                    }
                }
            }
        }
        Item{
            id: root_body
            height: parent.height - root.tab_bar_height
            width: parent.width
            StackLayout{
                id: root_body_stack
                anchors.fill: parent
                Repeater{
                    model: bufferModel
                    delegate: Item{
                        id: canvas
                        Component.onCompleted: {
                            if(model["source"] !== ""){
                                root_body_loader.source = model["source"];
                            }
                            else{
                                root_body_loader.sourceComponent = model["sourceComponent"];
                            }
                        }
                        Loader{
                            id: root_body_loader
                            anchors.fill: parent
                        }
                    }
                }
            }
        }
    }
}
