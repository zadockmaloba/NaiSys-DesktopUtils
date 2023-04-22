import QtQuick 2.12
import QtQuick.Controls
import libgui

NaiSysWindowPrivate {
    id: root

    Connections {
        target: NaiSysNotification

        function onNewNotification(type, message) {
            console.log("Testing notification signal handler.")
            switch (type) {
            case NaiSysNotification.INFO:
            case NaiSysNotification.MESSAGE:
                comp.color = "light grey"
                break
            case NaiSysNotification.WARNING:
                comp.color = "#fff9c4"
                break
            case NaiSysNotification.ERROR:
                comp.color = "#ff5252" //"#ef9a9a"
                break
            }
            comp_view.text = message
            comp.visible = true
        }
    }

    Flickable {
        z: 1000
        width: parent.width * 0.4
        height: parent.height
        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter
        contentWidth: width
        contentHeight: 100
        enabled: comp.visible
        NaiSysDiv {
            id: comp
            width: parent.width
            height: 100
            color: "light grey"
            opacity: 0.6
            radius: 8
            visible: false
            enabled: visible
            border_color: "grey"
            border_width: 2
            PopupView {
                id: comp_view
                anchors.fill: parent
            }
            PopupClose {
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.topMargin: 4
                anchors.leftMargin: 4
            }
        }
    }

    component PopupClose: NaiSysButton {
        width: 16
        height: 16
        radius: 8
        color: "grey"
        onClicked: comp.visible = false
        div.enable_shadow: false
        div.enable_bloom: false
    }

    component PopupView: Item {
        property alias text: popup_textArea.text
        property alias icon: popup_iconArea
        Image {
            id: popup_iconArea
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            width: parent.width * 0.25
        }
        NaiSysLabel {
            id: popup_textArea
            anchors.left: popup_iconArea.right
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            font.pixelSize: 14
        }
    }
}
