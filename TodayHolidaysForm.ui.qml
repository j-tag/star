import QtQuick 2.4
import QtQuick.Layouts 1.1
import "Main.js" as Main

Item {

    property alias flickableTodayHolidays: flickableTodayHolidays
    property alias rectBg: rectBg

    id: todayHolidays
    width: mainWindow.width/1.2
    height: 400
    Layout.minimumWidth: 400
    Layout.minimumHeight: 400

    Flickable {
        id: flickableTodayHolidays
        transformOrigin: Item.Center
        anchors.centerIn: parent
        width: todayHolidays.width/1.21
        height: 401
        contentHeight: itemTodayHolidays.height
        contentWidth: itemTodayHolidays.width


        Rectangle
        {
            id: rectBg
            color: Main.pageColor
            anchors.fill: itemTodayHolidays

            radius: 3
            opacity: .7

        }


        Item
        {
            id:itemTodayHolidays
            anchors.centerIn: parent
            width: todayHolidays.width/1.2
            height: 400


            Row {
                id: rowTodayHolidays
                width: itemTodayHolidays.width/1.2
                height: 200
                spacing: 2
                anchors.centerIn: parent


            }
        }
    }
}

