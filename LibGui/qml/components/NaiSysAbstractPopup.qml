import QtQuick 2.12
import QtQuick.Controls
import QtQuick.Layouts 1.12

Popup{
    id: root
    property Component cmp_delegate
    property double background_opacity: 0.98

    function setActiveComponent(comp){
        contentloader.sourceComponent = comp;
    }

    opacity: background_opacity

    Loader{
        id: contentloader
        anchors.fill: parent
        sourceComponent: cmp_delegate
    }
}
