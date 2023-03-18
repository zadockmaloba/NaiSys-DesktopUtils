import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.12

Item
{
    id: root
    function mdlToKeyArray(_mdl){
        var jsarr = [];
        if(_mdl){
            for (var i = 0; i < _mdl.count; ++i) jsarr.push(_mdl.get(i));
            var _keys = jsarr.map(function(element){return Object.keys(element)})
            return _keys[0];
        }
        return jsarr;
    }
    function mdlToValueArray(_mdl){
        var jsarr = [];
        if(_mdl){
            for (var i = 0; i < _mdl.count; ++i) jsarr.push(_mdl.get(i));
            var _keys = jsarr.map(function(element){return Object.keys(element)})[0];
            var _vals = []
            for (var j = 0; j < _keys.length; ++j) _vals.push(jsarr[0][_keys[j]]);
            return _vals;
        }
        return jsarr;
    }
    function formatStringArray(_arr){
        var _res = _arr ? _arr.map(function(i){return i.toUpperCase().replace("_", " ")}) : 0
        return _res
    }

    property ListModel mdl_data

    ScrollView{
        id: root_scrollArea
        anchors.fill: parent
        Grid{
            id: root_scrollArea_grid
            anchors.fill: parent
            columns: 2
            columnSpacing: 2
            rowSpacing: 2
            Repeater{
                model: formatStringArray(mdlToKeyArray(mdl_data))
                delegate: Rectangle{
                    height: 40
                    width: (root.width / 2) - 2
                    Row{
                        anchors.fill: parent
                        Item{
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
                        Rectangle{
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
