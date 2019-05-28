import QtQuick 2.7
import QtQuick.Controls 2.12

// Main page handler
import "../Main.js" as Main

Item {
    // Note: width and height must be set by caller

    property Item blurContent
    property Item mainContent
    property Item contentItem
    property alias paneMsg: paneMsg
    property alias msg: msg

    id: msg

    Rectangle
    {
        id: rectBackground
        color: "#000000"
        opacity: .5
        anchors.fill: msg
    }

    Pane {
        id: paneMsg
        anchors.centerIn: rectBackground
        clip: true
        width: msg.width/1.5
        height: msg.height/2
        scale: 0

        background: Rectangle
        {
            anchors.fill: parent
            radius: 5
            color: "#90ffffff"
        }

        contentItem: msg.contentItem

        Behavior on scale
        {

            NumberAnimation
            {
                duration: Main.msgShowDuration
                easing.type: Main.msgRectEasingType
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

    // Functions

    // Show message dialog
    function show() {
        paneMsg.scale = 1
        opacity = 1
    }

    // Close message dialog
    function close() {
        msg.opacity = 0
        paneMsg.scale = 0
        blurContent.opacity = 0
        mainContent.enabled = true
        mainWindow.header.enabled = true
    }

}

