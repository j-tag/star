import QtQuick 2.7
import QtQuick.Layouts 1.1
import "../Main.js" as Main

Item {

    property alias flickableTodayEvents: flickableTodayEvents
    property alias rectBg: rectBg

    id: todayEventsPage
    Layout.minimumWidth: 200
    Layout.minimumHeight: 200

    Flickable {
        id: flickableTodayEvents
        transformOrigin: Item.Center
        anchors.centerIn: parent
        width: todayEventsPage.width / 1.21
        height: todayEventsPage.height / 1.21
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
            width: todayEventsPage.width / 1.2
            height: todayEventsPage.height / 1.3

            Row {
                id: rowTodayEvents
                width: itemTodayEvents.width / 1.2
                height: itemTodayEvents.height / 1.1
                spacing: 2
                anchors.centerIn: parent

                Text {
                    text: "TODAY EVENTS"
                }
            }
        }
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
