// ************************************************
// 2022, Zadock Maloba <zadockmaloba@outlook.com>
// ************************************************
import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root
    property string text: ""
    property string text_size: "p"
    property alias font: root_text.font
    NaiSysText {
        id: root_text
        anchors.centerIn: parent
        text: qsTr(root.text)
        text_size: root.text_size
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        //fontSizeMode: Text.Fit
        onWidthChanged: _wdth => {
                            if (text !== "" && _wdth) {
                                var mul = root_text.font.pixelSize
                                var lngth = text.length * mul
                                var actl = root.width
                                var tmp = lngth > actl

                                if (tmp) {
                                    root_text.width = root.width
                                    //root_text.height = root.height * 0.5
                                    root_text.anchors.fill = parent
                                    //root_text.anchors.verticalCenter = parent.verticalCenter
                                }
                            }
                        }


        /*onTextChanged: _txt => {
                           if (_txt !== "") {
                               var mul = root_text.font.pixelSize
                               var lngth = _txt.length * mul
                               var actl = root.implicitWidth
                               var tmp = lngth > actl

                               if (tmp) {
                                   root_text.width = root.width
                                   root_text.anchors.fill = parent
                                   root_text.anchors.verticalCenter = parent.verticalCenter
                               }
                           }
                       }*/
    }
    //TODO: Implement editable property
}
