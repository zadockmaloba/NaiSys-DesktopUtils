import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import libgui

Item {
    id: root
    default property list<NaiSysTabElement> elements

    Column {
        id: root_layout
        anchors.fill: parent
        Item {
            id: header_area
            width: parent.width
            height: 35
            NaiSysDiv {
                id: header_background
                anchors.fill: parent
                anchors.topMargin: 2
                anchors.bottomMargin: 2
                anchors.leftMargin: 2
                anchors.rightMargin: 2
                color: "grey"
                radius: 4
                RowLayout {
                    id: header
                    anchors.fill: parent
                    anchors.topMargin: 2
                    anchors.bottomMargin: 2
                    anchors.leftMargin: 2
                    anchors.rightMargin: 2
                    Repeater {
                        model: elements
                        delegate: NaiSysButton {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            div.enable_shadow: false
                            div.enable_bloom: false
                            div.border.color: "black"
                            div.border.width: 1
                            color: "grey"
                            secondary_color: "light grey"
                            text: model.title
                        }
                    }
                }
            }
        }
        Item {
            id: body_area
            width: parent.width
            height: parent.height - header_area.height
        }
    }
}
