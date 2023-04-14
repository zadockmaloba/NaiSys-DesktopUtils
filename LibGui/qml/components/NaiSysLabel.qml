// ************************************************
// 2022, Zadock Maloba <zadockmaloba@outlook.com>
// ************************************************

import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root
    property string text: ""
    property string text_size: "p"
    NaiSysText {
        id: root_text
        anchors.centerIn: parent
        text: qsTr(root.text)
        text_size: root.text_size
    }
}
