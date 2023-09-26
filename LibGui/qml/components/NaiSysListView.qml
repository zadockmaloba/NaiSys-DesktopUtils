import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

NaiSysDiv {
    id: root
    property alias mdl_data: root_column_body_listView.model
    property Component cmp_delegate
    property string title: "Title"
    property bool displaySearchBox: true
    signal clicked(var index)
    signal rightClicked(var index, var xpos, var ypos)
    property int selectedIndex
    property int delegateHeight: 25
    property bool clipList: false
    property bool enableGlobalMapping: false
    property QtObject selectedData

    enable_bloom: false

    Column {
        id: root_column
        anchors.fill: parent
        Item {
            id: root_column_header
            width: parent.width
            height: displaySearchBox ? parent.height * 0.12 : parent.height * 0.06
            ColumnLayout {
                anchors.fill: parent
                Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Text {
                        id: root_column_header_title
                        anchors.centerIn: parent
                        text: qsTr(root.title)
                        font.pointSize: 12
                        font.family: "Arial"
                        font.bold: true
                    }
                }
                Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    visible: displaySearchBox
                    TextField {
                        id: root_column_header_searchBox
                        anchors.fill: parent
                        placeholderText: "Search..."
                    }
                }
            }
        }
        Item {
            id: root_column_body
            width: parent.width
            height: parent.height - root_column_header.height
            ListView {
                id: root_column_body_listView
                anchors.fill: parent
                clip: clipList
                spacing: 2
                delegate: Item {
                    width: root_column_body.width
                    height: delegateHeight

                    MouseArea {
                        id: mouseRegion
                        anchors.fill: parent
                        acceptedButtons: Qt.LeftButton | Qt.RightButton
                        onClicked: mouse => {
                                       if (mouse.button === Qt.LeftButton) {
                                           console.log(index)
                                           root.clicked(index)
                                           selectedData = root_column_body_listView.model
                                       } else if (mouse.button === Qt.RightButton) {
                                           var globalPos = enableGlobalMapping ? mapToGlobal(mouseX, mouseY) : Qt.point(mouseX, mouseY)
                                           root.rightClicked(index,
                                                             globalPos.x,
                                                             globalPos.y)
                                       }
                                   }
                    }

                    Loader {
                        anchors.fill: parent
                        property int modelIndex: index
                        property QtObject model_obj: model
                        sourceComponent: cmp_delegate
                    }
                }
            }
        }
    }
}
