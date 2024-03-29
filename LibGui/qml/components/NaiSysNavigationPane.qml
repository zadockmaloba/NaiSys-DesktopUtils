import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

NaiSysDiv {
    id: root
    property int int_layoutSpaceWidth
    property Loader ld_view
    property ListModel mdl_pages

    signal pageSelected(var page)

    enable_bloom: false

    Behavior on width {
        NumberAnimation {
            properties: "width"
            easing.type: "InOutQuad"
            duration: 200
        }
    }
    ColumnLayout {
        anchors.fill: parent
        spacing: 2
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        anchors.topMargin: 5
        anchors.bottomMargin: 5
        NaiSysButton {
            //FIXME: Binding loop
            Layout.fillWidth: true
            Layout.preferredHeight: 25
            Layout.minimumHeight: 25
            div.enable_bloom: false
            onClicked: {
                root.width = (root.width === 40 ? (int_layoutSpaceWidth * 0.2) : 40)
            }
            onWidthChanged: {
                if (root.width <= 40)
                    root.width = 40
            }
            Row {
                anchors.fill: parent
                anchors.leftMargin: 5
                Text {
                    width: parent.width - 40
                    anchors.verticalCenter: parent.verticalCenter
                    text: qsTr("Menu")
                    font.pointSize: 12
                    font.family: "Arial"
                    font.bold: true
                    visible: !(root.width === 40)
                }
                Image {
                    height: parent.height
                    width: 40
                    source: "qrc:/images/icons/images/misc-images/hamburger-menu.png"
                    fillMode: Image.PreserveAspectFit
                }
            }
        }
        Repeater {
            anchors.fill: parent
            model: mdl_pages
            delegate: NaiSysButton {
                Layout.fillWidth: true
                Layout.preferredHeight: 25
                Layout.minimumHeight: 25
                div.enable_bloom: false
                onClicked: {
                    ld_view.setSource(model["source"])
                    pageSelected(model["source"])
                }

                Row {
                    anchors.fill: parent
                    Text {
                        width: parent.width - 40
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.leftMargin: 10
                        text: qsTr(model["name"])
                        font.family: "Arial"
                        font.pointSize: 10
                        visible: !(root.width === 40)
                    }
                    Image {
                        height: parent.height
                        width: 40
                        source: model["icon"] ? model["icon"] : "qrc:/images/icons/images/icons/window.png"
                        fillMode: Image.PreserveAspectFit
                    }
                }
            }
        }
        Item {
            id: spacer
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}
