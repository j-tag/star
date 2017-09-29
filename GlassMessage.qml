import QtQuick 2.7
import QtQuick.Controls 2.0

// Main page handler
import "Main.js" as Main

Item {
    // Note: width and height must be set by caller

    property string strMessage
    property var blurContent
    property var mainContent

    id: msg

    Rectangle
    {
        id: rectBackground
        color: "#000000"
        opacity: .5
        anchors.fill: msg
    }


    Rectangle
    {
        id: rectMsg
        anchors.centerIn: rectBackground
        radius: 5
        color: "#ffffff"
        width: Qt.platform.os === "android" ? msg.width/1.2 : msg.width/2
        height : Qt.platform.os === "android" ? msg.height/1.5 : msg.height/3

        Text
        {
            id:textMsg
            text: strMessage
            anchors.fill: rectMsg
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.margins: 14
            font.pixelSize: 14

            wrapMode: Text.WordWrap
        }

        Button
        {
            anchors.horizontalCenter: rectMsg.horizontalCenter
            anchors.bottomMargin: 14
            anchors.bottom: rectMsg.bottom

            text: qsTr("تایید")

            onClicked:
            {
                msg.opacity = 0
                blurContent.opacity = 0
                mainContent.enabled = true
                mainWindow.toolBar.enabled = true
            }
        }
    }

    onOpacityChanged:
    {
        visible = msg.opacity === 0 ? false : true
    }

    Behavior on opacity
    {

        NumberAnimation
        {
            duration: Main.msgShowDuration
            easing.type: Main.msgEasingType
        }
    }
}

