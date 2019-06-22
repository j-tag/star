import QtQuick 2.12
import QtQuick.Layouts 1.12
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

            ColumnLayout {
                id: rowTodayHolidays
                width: itemTodayHolidays.width / 1.2
                height: itemTodayHolidays.height / 1.1
                spacing: 40
                anchors.fill: parent

                Text {
                    Layout.alignment: Qt.AlignCenter
                    topPadding: 20
                    text: qsTr("مناسبت‌های امروز")
                    font.pixelSize: 24
                }

                Text {
                    visible: todayEvents.holiday
                    color: "#ef3e3e"
                    Layout.alignment: Qt.AlignCenter
                    text: qsTr("تعطیل")
                    font.bold: true
                    font.pixelSize: 26
                }

                ListView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    model: todayEvents.events
                    delegate: Text {
                        width: parent.width - 20
                        horizontalAlignment: Text.AlignRight
                        text: modelData
                        font.pixelSize: 22
                    }
                }
            }
        }
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
