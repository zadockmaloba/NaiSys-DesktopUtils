import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Popup {
    id: root
    width: 250
    height: 150
    modal: true
    focus: true
    contentItem: NaiSysDiv {
        Column {
            anchors.fill: parent
            Item {
                height: parent.height * 0.3
                width: parent.width
                Text {
                    anchors.centerIn: parent
                    text: qsTr("Loading...")
                    font.pointSize: 12
                    font.family: "Arial"
                }
            }
            Item {
                height: parent.height * 0.7
                width: parent.width
                AnimatedImage {
                    id: loadingIcon
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                    source: "qrc:/dev.naisys.net/libgui/resources/loading4.gif"
                }
            }
        }
    }
}
