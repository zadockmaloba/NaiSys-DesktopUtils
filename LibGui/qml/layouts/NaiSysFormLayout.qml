import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: root
    function mdlToKeyArray(_mdl) {
        var jsarr = []
        if (_mdl) {
            for (var i in _mdl)
                jsarr.push(i)
        }
        return formatStringArray(jsarr)
    }
    function mdlToValueArray(_mdl) {
        var jsarr = []
        if (_mdl) {
            for (var i in _mdl)
                jsarr.push(_mdl[i])
        }
        return jsarr
    }
    function formatStringArray(_arr) {
        var _res = _arr ? _arr.map(function (i) {
            return i.toUpperCase().replace("_", " ")
        }) : 0
        return _res
    }

    property var mdl_data

    ScrollView {
        id: root_scrollArea
        anchors.fill: parent
        Grid {
            id: root_scrollArea_grid
            anchors.fill: parent
            columns: 2
            columnSpacing: 2
            rowSpacing: 2
            Repeater {
                model: mdlToKeyArray(mdl_data)
                delegate: Rectangle {
                    height: 40
                    width: (root.width / 2) - 2
                    Row {
                        anchors.fill: parent
                        Item {
                            height: parent.height
                            width: parent.width * 0.5
                            Text {
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                text: modelData
                                font.pointSize: 10
                                font.family: "Arial"
                                font.bold: true
                            }
                        }
                        Rectangle {
                            height: parent.height
                            width: parent.width * 0.5
                            color: "light grey"
                            Text {
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                text: mdlToValueArray(mdl_data)[index]
                                font.pointSize: 10
                                font.family: "Arial"
                                font.bold: false
                            }
                        }
                    }
                }
            }
        }
    }
}
