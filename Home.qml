import QtQuick 2.4
import "Main.js" as Main

HomeForm {
    flickableHome.rebound: Transition {
                           NumberAnimation {
                               properties: "x,y"
                               duration: Main.pageDuration
                               easing.type: Main.pageEasingType
                           }
                       }
}

