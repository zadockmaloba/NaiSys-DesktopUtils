import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../components"

Item {
    id: root
    property Component cmp_pageMenuBtns
    property ListModel mdl_pageArray
    property ListModel mdl_quickLinks: ListModel {
        ListElement {
            title: "Home"
        }
        ListElement {
            title: "View"
        }
    }

    ToolBar {
        id: root_header
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 0
        visible: false
        background: Rectangle {
            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: "#e0e0e0"
                }
                GradientStop {
                    position: 1
                    color: "#bdbdbd"
                }
            }
        }
        RowLayout {
            anchors.fill: parent
            spacing: 2
            RowLayout {
                Layout.fillHeight: true
                Repeater {
                    model: mdl_quickLinks
                    ToolButton {
                        Layout.fillHeight: true
                        Text {
                            anchors.centerIn: parent
                            text: model["title"]
                            font.pointSize: 10
                            font.family: "Arial"
                            color: "white"
                        }
                    }
                }
                ToolSeparator {
                    Layout.fillHeight: true
                }
                Loader {
                    id: root_header_loader
                    Layout.fillHeight: true
                    sourceComponent: cmp_pageMenuBtns
                }
            }
        }
    }
    Item {
        id: root_body
        anchors.top: root_header.bottom
        anchors.topMargin: 5
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        Item {
            id: root_body_contentDiv
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.right: root_body_sidePane.left
            Loader {
                id: root_body_contentDiv_loader
                anchors.fill: parent
                source: mdl_pageArray.get(0)["source"]
                onLoaded: {
                    console.log("[COMPONENT LOADED]")
                    if (root_body_contentDiv_loader.item.page_menu_bar) {
                        root.cmp_pageMenuBtns = root_body_contentDiv_loader.item.page_menu_bar
                        root_header_loader.visible = true
                        return
                    } else
                        root_header_loader.visible = false
                    return
                }
            }
        }
        NaiSysNavigationPane {
            id: root_body_sidePane
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.top: parent.top
            color: "#eceff1"
            shadow_offset_h: -4
            shadow_radius: 12
            implicitWidth: 40
            width: parent.width * 0.2
            int_layoutSpaceWidth: root_body.width
            ld_view: root_body_contentDiv_loader
            mdl_pages: mdl_pageArray
        }
    }
}
