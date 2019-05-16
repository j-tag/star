import QtQuick 2.7
import QtQuick.Layouts 1.1
import "../Main.js" as Main

Item {

    property alias flickableTodayHolidays: flickableTodayHolidays
    property alias rectBg: rectBg

    id: todayHolidays
    Layout.minimumWidth: 200
    Layout.minimumHeight: 200

    Flickable {
        id: flickableTodayHolidays
        transformOrigin: Item.Center
        anchors.centerIn: parent
        width: todayHolidays.width / 1.21
        height: todayHolidays.height / 1.21
        contentHeight: itemTodayHolidays.height
        contentWidth: itemTodayHolidays.width

        Rectangle {
            id: rectBg
            color: Main.pageColor
            anchors.fill: itemTodayHolidays

            radius: Main.pageRadius
            opacity: Main.pageOpacity
        }

        Item {
            id: itemTodayHolidays
            anchors.centerIn: parent
            width: todayHolidays.width / 1.2
            height: todayHolidays.height / 1.3

            Row {
                id: rowTodayHolidays
                width: itemTodayHolidays.width / 1.2
                height: itemTodayHolidays.height / 1.1
                spacing: 2
                anchors.centerIn: parent

                Text {
                    text: "TODAY HOLYDAYS"
                }
            }
        }
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
