import QtQuick 2.4
import QtQuick.Layouts 1.1

Item {

    property alias flickableTodayEvents: flickableTodayEvents
    property alias rectBg: rectBg

    id: todayEvents
    width: mainWindow.width/1.2
    height: 400
    Layout.minimumWidth: 400
    Layout.minimumHeight: 400

    Flickable {
        id: flickableTodayEvents
        transformOrigin: Item.Center
        anchors.centerIn: parent
        width: todayEvents.width/1.21
        height: 401
        contentHeight: itemTodayEvents.height
        contentWidth: itemTodayEvents.width


        Rectangle
        {
            id: rectBg
            color: "#979797"
            anchors.fill: itemTodayEvents

            radius: 3
            opacity: .7

        }


        Item
        {
            id:itemTodayEvents
            anchors.centerIn: parent
            width: todayEvents.width/1.2
            height: 400


            Row {
                id: rowTodayEvents
                width: itemTodayEvents.width/1.2
                height: 200
                spacing: 2
                anchors.centerIn: parent


            }
        }
    }
}

