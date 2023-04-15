// ************************************************
// 2022, Zadock Maloba <zadockmaloba@outlook.com>
// ************************************************

import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

NaiSysDiv {
    id: root
    property string slide_directory: ""
    property var slide_image_list: []

    QtObject {
        id: private_props
        property int nav_buttons_size: 40
        property int nav_buttons_radius: 6
    }

    Item {
        id: root_layout
        anchors.fill: parent
        anchors.topMargin: 2
        anchors.bottomMargin: 2
        anchors.leftMargin: 2
        anchors.rightMargin: 2
        SwipeView {
            id: swpView
            height: parent.height
            width: parent.width
            //NOTE: Limit clipping
            clip: true
            Repeater {
                id: swpView_repeater
                model: root.slide_image_list
                delegate: NaiSysTronCard {
                    id: trnCard
                    card_image_source: root.slide_directory+modelData
                    card_caption: modelData
                }
            }
            //card_image_source:
        }
        NaiSysButton {
            id: navBtn1
            anchors.left: parent.left
            width: private_props.nav_buttons_size
            height: private_props.nav_buttons_size
            radius: private_props.nav_buttons_radius
            anchors.verticalCenter: parent.verticalCenter
            text: "<"
            text_size: "h3"
        }
        NaiSysButton {
            id: navBtn2
            anchors.right: parent.right
            width: private_props.nav_buttons_size
            height: private_props.nav_buttons_size
            radius: private_props.nav_buttons_radius
            anchors.verticalCenter: parent.verticalCenter
            text: ">"
            text_size: "h3"
        }
    }
}
