// ************************************************
// 2022, Zadock Maloba <zadockmaloba@outlook.com>
// ************************************************

import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

AbstractButton {
    id: root
    property int radius: 0
    property string color: "grey"
    property string border_color: "white"
    property string secondary_color: "light grey"
    property string text_size: "p"

    //FIXME: Binding not deferred warnings
    background: Rectangle {
        id: root_background
        color: "grey"
        radius: root.radius
        border.color: root.border_color
        NaiSysLabel {
            anchors.fill: parent
            text: qsTr(root.text)
            text_size: root.text_size
        }
    }
    onPressedChanged: {
        root_background.color = root.pressed ? root.color : root.secondary_color
    }
}
