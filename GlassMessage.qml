import QtQuick 2.0
import QtQuick.Controls 1.3

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
        width: msg.width/2
        height : 114

        Text
        {
            id:textMsg
            text: strMessage
            anchors.centerIn: rectMsg
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

