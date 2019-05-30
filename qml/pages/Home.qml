import QtQuick 2.7
import "../Main.js" as Main

HomeForm {
    flickableHome.rebound: Transition {
                           NumberAnimation {
                               properties: "x,y"
                               duration: Main.pageDuration
                               easing.type: Main.pageEasingType
                           }
                       }

    textName.text: qsTr("سلام %1 حالت چطوره؟").arg(userDetails.name)
}

