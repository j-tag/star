import QtQuick 2.4
import "Main.js" as Main

TodayHolidaysForm {
    flickableTodayHolidays.rebound: Transition {
                           NumberAnimation {
                               properties: "x,y"
                               duration: Main.pageDuration
                               easing.type: Main.pageEasingType
                           }
                       }
}

