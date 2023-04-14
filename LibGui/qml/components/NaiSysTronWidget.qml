import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.12
import Qt5Compat.GraphicalEffects

Item {
    id: root
    property ListModel mdl_AppModel
    property Loader ld_AppLoader
    property int currContext : 0
    signal openNewTab(string m_name, string m_src)

    Rectangle{
        id: tronDiv
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
        height: parent.height * 0.7
        radius: 5
        color: "#b2dfdb"
        gradient: Gradient{
            GradientStop{position: 0; color: "#b2dfdb"}
            GradientStop{position: 1; color: "#e0f7fa"}
        }
        Item {
            id: imageDiv
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            width: parent.width * 0.4
            Image {
                id: tronImg
                anchors.fill: parent
                source: mdl_AppModel.get(0).imgurl
                fillMode: Image.PreserveAspectCrop
                layer.enabled: true
                layer.effect: OpacityMask {
                    maskSource: Item {
                        width: imageDiv.width
                        height: imageDiv.height
                        Rectangle {
                            anchors.fill: parent
                            radius: 5
                        }
                    }
                }
            }
        }
        Item{
            id: tronControlsDiv
            anchors.top: parent.top
            anchors.topMargin: 5
            anchors.left: imageDiv.right
            anchors.leftMargin: 5
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            Button{
                id: tronOpenBtn
                anchors.top: parent.top
                anchors.left: parent.left
                text: "Open"
                onClicked: {
                    root.openNewTab(mdl_AppModel.get(currContext).name, mdl_AppModel.get(currContext).cardobj)
                }
            }
        }
    }
    ScrollView{
        id: btnsDiv
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: tronDiv.bottom
        anchors.topMargin: -(parent.height * 0.15)
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: (parent.height * 0.15)
        contentHeight: -1
        clip: true
        Row{
            anchors.fill: parent
            spacing: 5
            Repeater{
                model: mdl_AppModel
                delegate: Rectangle{
                    MouseArea{
                        id:msr
                        anchors.fill: parent
                        onPressed: {
                            tronImg.source = model.imgurl
                            currContext = index
                        }
                    }
                    opacity: 0.97
                    radius: 5
                    height: btnsDiv.height * 0.9
                    width: root.width / 4
                    gradient: Gradient{
                        GradientStop{position: 0; color: msr.pressed ? "#b2dfdb" :"#b0bec5"}
                        GradientStop{position: 1; color: "#eceff1"}
                    }
                    Text {
                        id: cardTitle
                        anchors.verticalCenter: parent.verticalCenter
                        width: 150
                        height: 50
                        text: qsTr(model.name)
                        font.bold: false
                        font.family: "Arial"
                        color: "white"
                        font.pointSize: 20
                    }
                }
            }
        }
    }
}
