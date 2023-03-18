import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root
    function newTab(m_name, m_source){
        bufferModel.append({name: m_name, source: m_source});
    }
    function newTabComponent(m_name, m_source){
        bufferModel.append({name: m_name, source: "", sourceComponent: m_source});
    }
    function removeTab(m_index) {
        bufferModel.remove(m_index);
    }

    property int headerHeight: 30
    property bool initAll: false
    property ListModel stackModel: ListModel{
        ListElement{name: "Home"; source: ""}
        ListElement{name: "Settings"; source: ""}
    }
    property Component homeView
    ListModel{id: bufferModel}
    Menu{
        id: contextMenu
        x: addTabButton.x
        y: addTabButton.y + addTabButton.height
        Repeater{
            model: stackModel
            delegate: MenuItem{
                text: model["name"]
                onClicked: {
                    root.newTab(text, model["source"]);
                }
            }
        }
    }

    Component.onCompleted: {
        if(!homeView){
            if(root.initAll){
                for(var i=0; i<stackModel.count;++i){
                    bufferModel.append(stackModel.get(i));
                }
            }
            else bufferModel.append(stackModel.get(0));
        }
        else{
            bufferModel.append({name: "Home", source: "", sourceComponent: homeView});
        }
   }

    Column{
        id: root_layout
        anchors.fill: parent
        Rectangle{
            id: root_header
            height:headerHeight
            width: parent.width
            color: "light gray"
            ScrollView{
                anchors.fill: parent
                anchors.leftMargin: 2
                anchors.rightMargin: 2
                anchors.bottomMargin: 2
                anchors.topMargin: 2
                Row{
                    id: root_header_layout
                    anchors.fill: parent
                    Repeater{
                        model: bufferModel
                        delegate: ToolButton{
                            height: parent.height
                            width: 120
                            text: model["name"]
                            font.bold: true
                            onClicked: {
                                root_body_stack.currentIndex = index;
                            }
                            background: Rectangle{
                                radius: 2
                                opacity: 0.7
                                border.color: "white"
                                color: index === root_body_stack.currentIndex ? "grey" : "light grey"
                                gradient: Gradient{
                                    GradientStop{position: 0; color: "light grey"}
                                    GradientStop{position: 1; color: index === root_body_stack.currentIndex ? "grey" : "light grey"}
                                }
                            }
                        }
                    }
                    Button{
                        id: addTabButton
                        height: parent.height
                        width: 40
                        enabled: !initAll
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
            height: parent.height - headerHeight
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
