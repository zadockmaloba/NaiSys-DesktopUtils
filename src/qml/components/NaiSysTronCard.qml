// ************************************************
// 2022, Zadock Maloba <zadockmaloba@outlook.com>
// ************************************************

import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

NaiSysButton {
    id: root
    QtObject {
        id: private_props
        property bool card_caption_visible: false
    }
    property int card_border_radius: 0
    property int card_bg_opacity: 1
    property string card_image_source: ""
    property string card_bg_color: "light grey"
    property string card_caption: "Image Card"

    onHoveredChanged: {
        root.hovered ? private_props.card_caption_visible = true :
                       private_props.card_caption_visible = false
    }

    background: Rectangle {
        color: card_bg_color
        radius: card_border_radius
        opacity: card_bg_opacity

        Item {
            id: bg_layout_imgDiv
            width: parent.width
            height: parent.height
            Image {
                id: img
                anchors.fill: parent
                source: root.card_image_source
                fillMode: Image.PreserveAspectCrop
            }
            Rectangle {
                id: bg_layout_lblDiv
                width: parent.width * 0.35
                height: parent.height
                opacity: 0.7
                visible: private_props.card_caption_visible
                NaiSysLabel{
                    anchors.fill: parent
                    text: root.card_caption
                }
            }
        }
    }
}
