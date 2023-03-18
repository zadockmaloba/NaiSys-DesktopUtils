// ************************************************
// 2022, Zadock Maloba <zadockmaloba@outlook.com>
// ************************************************

import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: root
    //This property contains a dictionary of menubar items and their actions
    property ListModel menu_bar_items

    Row {
        id: root_layout
        anchors.fill: parent
        Repeater {
            id: root_layout_btnRepeater
            model: root.menu_bar_items
            delegate: Thx_MenuButton {
                height: root_layout.height
                width: 80 // Avoid explicit bindings
                text: model["name"]
                onClicked: model["action"]()
            }
        }
    }
}
