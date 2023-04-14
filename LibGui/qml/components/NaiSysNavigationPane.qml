import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.12

Rectangle{
    id: root
    property int int_layoutSpaceWidth
    property Loader ld_view
    property ListModel mdl_pages

    Behavior on width{
        NumberAnimation{properties: "width"; easing.type: "InOutQuad"; duration: 200}
    }
    Column{
        anchors.fill: parent
        spacing: 2
        ToolButton{
            //FIXME: Binding loop
            width: root.width
            height: 25
            onClicked: {
                root.width = (root.width === 40 ? (int_layoutSpaceWidth * 0.2) : 40);
            }
            onWidthChanged: {
                if( root.width <= 40 ) root.width = 40;
            }
            Row{
                anchors.fill: parent
                Text {
                    height: parent.height
                    width: parent.width  - 40
                    text: qsTr("Menu")
                    font.pointSize: 12
                    font.family: "Arial"
                    font.bold: true
                    visible: !(root.width === 40)
                }
                Image{
                    height: parent.height
                    width: 40
                    source: "qrc:/images/icons/images/misc-images/hamburger-menu.png"
                    fillMode: Image.PreserveAspectFit
                }
            }
        }
        Repeater{
            anchors.fill: parent
            model: mdl_pages
            delegate: ItemDelegate{
                width: root.width
                height: 25
                onClicked: {
                    ld_view.setSource(model["source"]);
                }
                Rectangle{
                    anchors.fill: parent
                    opacity: 0.3
                }
                Row{
                    anchors.fill: parent
                    Text {
                        height: parent.height
                        width: parent.width  - 40
                        text: qsTr(model["name"])
                        font.family: "Arial"
                        font.pointSize: 10
                        visible: !(root.width === 40)
                    }
                    Image{
                        height: parent.height
                        width: 40
                        source: model["icon"] ? model["icon"] : "qrc:/images/icons/images/icons/window.png"
                        fillMode: Image.PreserveAspectFit
                    }
                }
            }
        }
    }
}
