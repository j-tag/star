import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
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
                spacing: 10
                anchors.fill: parent

                Text {
                    Layout.alignment: Qt.AlignCenter
                    topPadding: 20
                    color: Main.textColor
                    text: qsTr("مناسبت‌های امروز")
                    font.pointSize: 14
                }

                Text {
                    visible: todayEvents.holiday
                    color: "#ef3e3e"
                    Layout.alignment: Qt.AlignCenter
                    text: qsTr("تعطیل")
                    font.bold: true
                    font.pixelSize: 26
                }

                Text {
                    Layout.alignment: Qt.AlignCenter
                    color: Main.textColor
                    text: todayEvents.persianDate
                    font.pixelSize: 16
                }

                Text {
                    visible: todayEvents.events.length === 0
                    Layout.alignment: Qt.AlignCenter
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: Main.textColor
                    text: qsTr("مناسبتی برای امروز وجود ندارد.")
                    font.bold: true
                    font.pixelSize: 22
                }

                ListView {
                    visible: todayEvents.events.length > 0
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    clip: true
                    model: todayEvents.events
                    delegate: Text {
                        width: parent.width - 20
                        horizontalAlignment: Text.AlignRight
                        color: Main.textColor
                        text: modelData
                        font.pixelSize: 22
                    }

                    ScrollBar.vertical: ScrollBar {
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
