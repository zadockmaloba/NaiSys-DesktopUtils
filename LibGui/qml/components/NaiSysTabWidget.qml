import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import libgui

Item {
    id: root
    default property list<NaiSysTabElement> elements
    property list<NaiSysTabElement> elements_buffer

    function newTab(tabIdentifier) {
        elements_buffer.push(elements[tabIdentifier])
    }

    function closeTab(tabIdentifier) {
        elements_buffer.splice(tabIdentifier, 1)
    }

    Component.onCompleted: {
        for (var i in elements) {
            if (elements[i].visible)
                elements_buffer.push(elements[i])
        }
    }

    Column {
        id: root_layout
        anchors.fill: parent
        Item {
            id: header_area
            width: parent.width
            height: 40
            NaiSysDiv {
                id: header_background
                anchors.fill: parent
                anchors.topMargin: 2
                anchors.bottomMargin: 2
                anchors.leftMargin: 2
                anchors.rightMargin: 2
                color: "light grey"
                radius: 4
                RowLayout {
                    id: header
                    anchors.fill: parent
                    anchors.topMargin: 2
                    anchors.bottomMargin: 2
                    anchors.leftMargin: 2
                    anchors.rightMargin: 2
                    Repeater {
                        model: elements_buffer
                        delegate: NaiSysButton {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            div.enable_shadow: false
                            div.enable_bloom: false
                            div.border.color: "black"
                            div.border.width: 0
                            color: index === body_area_stack.currentIndex ? "grey" : "light grey"
                            secondary_color: "light grey"
                            text: model.title
                            hoverEnabled: true
                            onClicked: {
                                body_area_stack.currentIndex = index
                            }
                            NaiSysButton {
                                id: close_button
                                anchors.left: parent.left
                                anchors.verticalCenter: parent.verticalCenter
                                height: parent.height * 0.5
                                width: height
                                anchors.leftMargin: 5
                                div.enable_bloom: false
                                // div.enable_shadow: false
                                div.color: "#c14b45"
                                visible: model.closable && parent.hovered
                                radius: width * 0.5
                                onClicked: closeTab(index)
                            }
                        }
                    }
                }
            }
        }
        Item {
            id: body_area
            width: parent.width
            height: parent.height - header_area.height
            StackLayout {
                id: body_area_stack
                anchors.fill: parent
                Repeater {
                    model: elements_buffer
                    delegate: Loader {
                        Component.onCompleted: {
                            if (model.source === "") {
                                sourceComponent = model.sourceComponent
                            } else {
                                source = model.source
                            }
                        }
                    }
                }
            }
        }
    }
}
