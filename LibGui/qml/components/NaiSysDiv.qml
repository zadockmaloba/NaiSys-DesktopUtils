import QtQuick
import Qt5Compat.GraphicalEffects

Item {
    id: root
    property string color: "#ffffff"
    property alias border: background.border
    property string border_color: color
    property int border_width: 0
    property int radius: 2
    property double shadow_radius: 8
    property int shadow_samples: 17
    property int shadow_offset_v: 4
    property int shadow_offset_h: 4
    property bool enable_shadow: true
    property bool enable_bloom: true

    Rectangle {
        id: background
        anchors.fill: parent
        color: root.color
        border.color: root.border_color
        border.width: root.border_width
        radius: root.radius
    }
    DropShadow {
            anchors.fill: background
            visible: root.enable_shadow
            horizontalOffset: root.shadow_offset_h
            verticalOffset: root.shadow_offset_v
            radius: root.shadow_radius
            samples: root.shadow_samples
            color: "grey"
            source: background
    }
    DropShadow {
            anchors.fill: background
            visible: root.enable_bloom
            horizontalOffset: -(root.shadow_offset_h)
            verticalOffset: -(root.shadow_offset_v)
            radius: root.shadow_radius
            samples: root.shadow_samples
            color: "white"
            source: background
    }
}
