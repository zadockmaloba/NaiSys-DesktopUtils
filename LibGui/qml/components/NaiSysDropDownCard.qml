import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

NaiSysButton {
    id: root

    property int min_height: 60
    property int max_height: 300
    property string title: ""
    property string nameRole
    property var m_items

    height: min_height
    onClicked: {
        if (height === min_height)
            height = 300
        else
            height = min_height
    }
    div.enable_bloom: false

    Column {
        anchors.fill: parent
        Item {
            id: header
            width: parent.width
            height: min_height
            NaiSysLabel {
                anchors.fill: parent
                text: root.title
                text_size: "h2"
            }
        }
        Rectangle {
            id: seperator
            width: parent.width
            height: 1
            color: "grey"
            visible: root.height === max_height
        }
        Item {
            id: body
            width: parent.width
            height: parent.height - (header.height + seperator.height)
            ScrollView {
                anchors.fill: parent
                clip: true
                anchors.leftMargin: 5
                anchors.rightMargin: 5
                anchors.topMargin: 5
                anchors.bottomMargin: 5
                //orientation: Qt.Horizontal
                Row {
                    anchors.fill: parent
                    spacing: 5
                    Repeater {
                        model: m_items
                        delegate: NaiSysButton {
                            div.border_color: "grey"
                            div.border.width: 1
                            anchors.verticalCenter: parent.verticalCenter
                            width: 100
                            height: 100
                            text: model[nameRole]
                        }
                    }
                }
            }
        }
    }
}
