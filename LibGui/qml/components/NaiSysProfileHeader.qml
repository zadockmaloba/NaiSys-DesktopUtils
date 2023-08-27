import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: root

    property string header_img_dir: "qrc:/background/images/vector-art-5-full.jpg"
    property string profile_img_dir: "qrc:/icons/images/misc-images/default-pfp.png"
    property string profile_title: "...."
    property string accent_color: "#eceff1"
    property string background_color: "#eceff1"

    Rectangle {
        color: background_color
        anchors.fill: parent
        Image {
            anchors.fill: parent
            opacity: 0.6
            fillMode: Image.PreserveAspectCrop
            source: header_img_dir
        }
        Column {
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: root_body_profileHeader_picture_div.left
            anchors.topMargin: 2
            anchors.leftMargin: 2
            anchors.bottomMargin: 2
            anchors.rightMargin: 2
            Rectangle {
                width: parent.width
                height: parent.height * 0.2
                opacity: 0.8
                color: accent_color
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    opacity: 1
                    color: "white"
                    font.pointSize: 12
                    font.family: "Arial"
                    font.bold: true
                    text: profile_title
                }
            }
        }
        Rectangle {
            id: root_body_profileHeader_picture_div
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.topMargin: 2
            anchors.leftMargin: 2
            anchors.bottomMargin: 2
            anchors.rightMargin: 2
            width: parent.width * 0.3
            opacity: 0.92
            color: accent_color
            Image {
                id: root_body_profileHeader_picture
                anchors.fill: parent
                source: profile_img_dir
                fillMode: Image.PreserveAspectFit
            }
        }
    }
}
