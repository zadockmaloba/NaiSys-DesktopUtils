import QtQuick
import QtQuick.Controls

NaiSysButton {
    id: root
    property bool selected: false
    property bool single_select: false

    div.border_width: 2
    div.border_color: selected ? "purple" : "grey"

    QtObject {
        id: p
        property int click_count: 0
    }

    Rectangle {
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.topMargin: 5
        anchors.rightMargin: 5
        width: parent.width * 0.14
        height: width
        radius: width * 0.5
        color: "purple"
        visible: selected
    }

    onClicked: {
        if (p.click_count == 0) {
            selected = !selected

            root.single_select ? p.click_count = 1 : p.click_count = 0
        }
    }
}
