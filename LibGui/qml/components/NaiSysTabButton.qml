// ************************************************
// 2022, Zadock Maloba <zadockmaloba@outlook.com>
// ************************************************
import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

AbstractButton {
    id: root
    property bool button_closable: true
    property string button_color: "light grey"
    property alias div: bg

    anchors.topMargin: 2
    anchors.bottomMargin: 2
    anchors.rightMargin: 2
    anchors.leftMargin: 2
    background: NaiSysDiv {
        id: bg
        color: root.button_color
        NaiSysLabel {
            anchors.fill: parent
            text: qsTr(root.text)
        }
    }
}
