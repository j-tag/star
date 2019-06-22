import QtQuick 2.7
import "../Main.js" as Main

TodayHolidaysForm {
    Connections {
        target: oauth2
        onLoginResult: {
            // result -> bool
            // strMessage -> QString

            if(result === true) {
                // Login was successful
                todayEvents.reload()
            }
        }
    }

    flickableTodayHolidays.rebound: Transition {
                           NumberAnimation {
                               properties: "x,y"
                               duration: Main.pageDuration
                               easing.type: Main.pageEasingType
                           }
                       }
}

