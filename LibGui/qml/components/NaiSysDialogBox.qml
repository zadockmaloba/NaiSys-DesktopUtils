import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12


Item {
    id: root
    property string str_dmessage: "Message : "
    property Component obj_delegate

    signal closeDialog()
    signal acceptDialog()

    Rectangle{
        anchors.fill: parent
        radius: 5
        color: "light grey"
        opacity: 0.95
        Item {
            id: msgArea
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: parent.height * 0.7
            ColumnLayout{
                anchors.fill: parent
                Label {
                    Layout.fillWidth: true; Layout.fillHeight: true
                    wrapMode: Text.WordWrap
                    text: qsTr(str_dmessage)
                }
                Loader{
                    Layout.fillWidth: true; Layout.fillHeight: true
                    sourceComponent: obj_delegate
                }
            }
        }
        RowLayout{
            anchors.top: msgArea.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            Button{
                text: "Cancel"
                Layout.fillWidth: true; Layout.fillHeight: true
                onClicked: closeDialog()
            }
            Button{
                text: "Okay"
                Layout.fillWidth: true; Layout.fillHeight: true
                onClicked: acceptDialog()
            }
        }
    }
}
