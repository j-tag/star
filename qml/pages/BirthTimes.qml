import QtQuick 2.7
import QtQuick.Layouts 1.12

import "../Main.js" as Main

Item
{

    Timer {
        running: true
        repeat: true
        interval: 1000
        onTriggered: userDetails.updateAge()
    }

    ColumnLayout {
        width: parent.width

        Text {
            id: birthInSecond
            Layout.alignment: Qt.AlignHCenter
            text: "سن شما به ثانیه: " + Main.englishNumberToPersian(userDetails.birthdayInSeconds) + " ثانیه"

        }
        Text {
            id: birthInMinute
            Layout.alignment: Qt.AlignHCenter
            text: "سن شما به دقیقه: " + Main.englishNumberToPersian(userDetails.birthdayInMinutes) + " دقیقه"
        }
        Text {
            id: birthInHour
            Layout.alignment: Qt.AlignHCenter
            text: "سن شما به ساعت: " + Main.englishNumberToPersian(userDetails.birthdayInHours) + " ساعت"
        }
        Text {
            id: birthInDay
            Layout.alignment: Qt.AlignHCenter
            text: "سن شما به روز: " + Main.englishNumberToPersian(userDetails.birthdayInDays) + " روز"
        }
        Text {
            id: birthInWeek
            Layout.alignment: Qt.AlignHCenter
            text: "سن شما به هفته: " + Main.englishNumberToPersian(userDetails.birthdayInWeeks) + " هفته"
        }
        Text {
            id: birthInMonth
            Layout.alignment: Qt.AlignHCenter
            text: "سن شما به ماه: " + Main.englishNumberToPersian(userDetails.birthdayInMonths) + " ماه"
        }
        Text {
            id: birthInSeason
            Layout.alignment: Qt.AlignHCenter
            text: "سن شما به فصل: " + Main.englishNumberToPersian(userDetails.birthdayInSeasons) + " فصل"
        }
        Text {
            id: birthInYear
            Layout.alignment: Qt.AlignHCenter
            text: "سن شما به سال: " + Main.englishNumberToPersian(userDetails.birthdayInYears) + " سال"
        }
    }
}









/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
