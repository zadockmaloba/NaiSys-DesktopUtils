// ************************************************
// 2022, Zadock Maloba <zadockmaloba@outlook.com>
// ************************************************

import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

NaiSysButton {
    id: root
    property int card_border_radius: 0
    property int card_bg_opacity: 1
    property string card_image_source: ""
    property string card_bg_color: "light grey"
    property string card_caption: "Image Card"

    background: Rectangle {
        color: card_bg_color
        radius: card_border_radius
        opacity: card_bg_opacity
        Column {
            id: bg_layout
            anchors.fill: parent
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            anchors.leftMargin: 2
            anchors.rightMargin: 2
            Item {
                id: bg_layout_imgDiv
                width: parent.width
                height: parent.height * 0.7
                Image {
                    id: img
                    anchors.fill: parent
                    source: root.card_image_source
                    fillMode: Image.PreserveAspectCrop
                }
            }
            Item {
                id: bg_layout_lblDiv
                width: parent.width
                height: parent.height * 0.3
                NaiSysLabel{
                    anchors.fill: parent
                    text: root.card_caption
                }
            }
        }
    }
}
