import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import libgui

// import "networkmethods.js" as NetH
ListView {
    id: root
    property string groupRole: ""
    property string groupTitleRole: ""
    property var groupList: []
    property var data: []

    function groupBy(mdl, rl) {
        let ret = []
        const uniqueNames = []
        const seenNames = {}

        mdl.forEach(item => {
                        if (!seenNames[item[rl]]) {
                            uniqueNames.push(item[rl])
                            seenNames[item[rl]] = true
                        }
                    })

        root.groupList = uniqueNames
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

        return ret
    }

    model: groupBy(data, root.groupRole)
    delegate: NaiSysDropDownCard {
        width: root.width
        title: groupList[index]
        items: model[title]
    }
}
