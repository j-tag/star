import QtQuick 2.7
import QtQuick.Layouts 1.12
import "../Main.js" as Main

Item {

    property alias flickableTodayEvents: flickableTodayEvents
    property alias rectBg: rectBg
    property alias gridviewTodayEvents: gridviewTodayEvents

    id: todayTasksPage
    Layout.minimumWidth: 200
    Layout.minimumHeight: 200

    Flickable {
        id: flickableTodayEvents
        transformOrigin: Item.Center
        anchors.centerIn: parent
        width: todayTasksPage.width / 1.21
        height: todayTasksPage.height / 1.21
        contentHeight: itemTodayEvents.height
        contentWidth: itemTodayEvents.width

        Rectangle {
            id: rectBg
            color: Main.pageColor
            anchors.fill: itemTodayEvents

            radius: Main.pageRadius
            opacity: Main.pageOpacity
        }

        Item {
            id: itemTodayEvents
            anchors.centerIn: parent
            width: todayTasksPage.width / 1.2
            height: todayTasksPage.height / 1.3

            GridView {
                id: gridviewTodayEvents
                width: itemTodayEvents.width / 1.2
                height: itemTodayEvents.height / 1.1
                anchors.fill: parent
                cellWidth: width / Math.floor(width / 200)
                cellHeight: 240
                clip: true
                layoutDirection: Qt.RightToLeft

                model: todayTasks.tasks
            }
        }
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
