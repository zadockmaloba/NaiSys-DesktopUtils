// ************************************************
// 2022, Zadock Maloba <zadockmaloba@outlook.com>
// ************************************************
import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

AbstractButton {
    id: root
    property int radius: 4
    property string color: "light grey"
    property string border_color: color
    property string secondary_color: "grey"
    property string text_size: "p"
    property alias div: root_background

    //FIXME: Binding not deferred warnings
    background: NaiSysDiv {
        id: root_background
        color: root.color
        radius: root.radius
        border_color: root.border_color
        NaiSysLabel {
            anchors.fill: parent
            text: qsTr(root.text)
            text_size: root.text_size
        }
    }
    onPressedChanged: {
        root_background.color = root.pressed ? root.secondary_color : root.color
    }
}
