// ************************************************
// 2022, Zadock Maloba <zadock.maloba@stream4.tech>
// ************************************************

import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Text {
    id: root
    property string text_size: "p" //p,h1,h2,h3,h4
    font.family: "Arial"
    font.pointSize: {
                        switch(root.text_size){
                            case "p": return 9;
                            case "h1": return 32;
                            case "h2": return 24;
                            case "h3": return 18;
                            case "h4": return 13;
                            default: return 9;
                        }
                    }
    //FIXME: Binding loop over here...
    //font.bold: font.pointSize >= 18;

    //FIXME: This is a horrible work around to be removed
    font.bold: text_size !== "p";
}
