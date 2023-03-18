// ************************************************
// 2022, Zadock Maloba <zadockmaloba@outlook.com>
// ************************************************

import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root
    //This property is used to dictate whether the view displays a menu bar
    property bool menu_bar_show: false
    property int menu_bar_height: 28
    //This property contains a dictionary of menubar items and their actions
    property ListModel menu_bar_items: ListModel{
        ListElement{name:"File"; action:()=>{console.log("File clicked")}}
        ListElement{name:"Home"; action:()=>{console.log("Home clicked")}}
        ListElement{name:"Settings"; action:()=>{console.log("Settings clicked")}}
    }
    property string menu_bar_color: "light grey"

    Thx_MenuBar{
        id: root_menuBar
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: menu_bar_height
        color: menu_bar_color
        visible: root.menu_bar_show
        menu_bar_items: root.menu_bar_items
    }
}
