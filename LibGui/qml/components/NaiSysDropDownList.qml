import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: root
    required property var m_data
    required property string groupRole
    required property string nameRole
    property int spacing: 5

    QtObject {
        id: p
        property var groupList: ([])
        property var sorted: groupBy(m_data, root.groupRole)
    }
    function groupBy(mdl, rl) {
        let ret = []
        var uniqueNames = []
        var seenNames = {}

        mdl.forEach(item => {
                        if (!seenNames[item[rl]]) {
                            uniqueNames.push(item[rl])
                            seenNames[item[rl]] = true
                        }
                    })

        p.groupList = uniqueNames
        for (var i in uniqueNames) {
            console.log(uniqueNames[i])

            const groupedData = mdl.reduce((result, item) => {
                                               const key = uniqueNames[i]
                                               if (!result[key]) {
                                                   result[key] = []
                                               }
                                               if (item[rl] === key) {
                                                   result[key].push(item)
                                               }
                                               return result
                                           }, {})
            ret.push(groupedData)
        }

        //console.log(JSON.stringify(ret))
        return ret
    }

    ListView {
        anchors.fill: parent
        spacing: root.spacing
        model: p.sorted
        delegate: NaiSysDropDownCard {
            width: root.width
            title: p.groupList[index]
            items: model[root.title]
            nameRole: root.nameRole
        }
    }
}
