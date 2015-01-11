import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtGraphicalEffects 1.0


// Main page js file
import "Main.js" as Main

ApplicationWindow {
    id: mainWindow
    title: qsTr("ستاره")
    width: 740
    height: 480
    minimumWidth: 600
    minimumHeight: 480
    visible: true

    toolBar: ToolBar
    {

        Row
        {

            ToolButton
            {
                id:toolBtnHome
                iconSource: "qrc:/Images/toolbar-home.png"
                width: 32
                height: 32


                onClicked:
                {
                    stack.push(home)

                    Main.disablePages(home)
                    Main.changeBackground()
                }
            }

            ToolButton
            {
                id:toolBtnTodayHolidays
                iconSource: "qrc:/Images/toolbar-todayholidays.png"
                width: 32
                height: 32

                onClicked:
                {
                    stack.push(todayHolidays)

                    Main.disablePages(todayHolidays)
                    Main.changeBackground()
                }
            }

            ToolButton
            {
                id:toolBtnTodayEvents
                iconSource: "qrc:/Images/toolbar-todayevents.png"
                width: 32
                height: 32

                onClicked:
                {
                    stack.push(todayEvents)

                    Main.disablePages(todayEvents)
                    Main.changeBackground()
                }

            }

            ToolButton
            {
                id:toolBtnMsgTest
                iconSource: "qrc:/Images/toolbar-todayholidays.png"
                width: 32
                height: 32

                onClicked:
                {
                    Main.showMessage("تاریخ شمسی امروز: " + JDate.getCurrentJalaliDate())
                }

            }

            ToolButton
            {
                id:toolBtnFlipTest
                iconSource: "qrc:/Images/toolbar-todayholidays.png"
                width: 32
                height: 32

                onClicked:
                {
                    flipableMainWindow.flipped = !flipableMainWindow.flipped
                }

            }
        }
    }


    Flipable
    {
        id: flipableMainWindow
        width: mainWindow.width
        height: mainWindow.height

        property bool flipped: false

        front: mainContent
        back: tt

        transform: Rotation
        {
            id: rotation
            origin.x: flipableMainWindow.width/2
            origin.y: flipableMainWindow.height/2
            axis.x: 1; axis.y: 0; axis.z: 0     // set axis.x to 1 to rotate around x-axis
            angle: 0    // the default angle
        }

        states: State
        {
            name: "back"
            PropertyChanges { target: rotation; angle: 180 }
            when: flipableMainWindow.flipped
        }

        transitions: Transition
        {
            NumberAnimation { target: rotation; property: "angle"; duration: Main.flipDuration; easing.type: Main.flipEasingType}
        }
    }

    Item
    {
        id: tt

        width: mainWindow.width
        height: mainWindow.height

        Rectangle
        {
            anchors.fill: tt
            color: "red"
        }

        Text {
            id: testText
            anchors.centerIn: parent
            text: qsTr("TODO : Calendar placeholder")
        }
    }


    Item {
        id: mainContent
        width: mainWindow.width
        height: mainWindow.height

        // Background image 1
        Image {
            id: imgBackground
            anchors.fill: parent
            fillMode: Image.PreserveAspectCrop
            source: "qrc:/Images/background.png"
            opacity: 1

            Behavior on opacity
            {
                NumberAnimation
                {
                    easing.type: Main.bgEasingType
                    duration: Main.bgDuration
                }
            }
        }

        // Background image 2
        Image {
            id: imgBackground2
            fillMode: Image.PreserveAspectCrop
            source: "qrc:/Images/background2.png"
            opacity: 0
            anchors.fill: imgBackground

            Behavior on opacity
            {
                NumberAnimation
                {
                    easing.type: Main.bgEasingType
                    duration: Main.bgDuration
                }
            }
        }

        // Background image 3
        Image {
            id: imgBackground3
            fillMode: Image.PreserveAspectCrop
            source: "qrc:/Images/background3.png"
            opacity: 0
            anchors.fill: imgBackground

            Behavior on opacity
            {
                NumberAnimation
                {
                    easing.type: Main.bgEasingType
                    duration: Main.bgDuration
                }
            }
        }


        StackView {
            id: stack
            initialItem: home

            Home
            {
                id: home
            }


            TodayHolidays
            {
                id: todayHolidays
                visible: false
            }

            TodayEvents
            {
                id: todayEvents
                visible: false
            }
        }

    }


    GlassMessage
    {
        id: glassMessage
        opacity: 0
        z:114// Brings messagebox to top
        anchors.centerIn: mainContent
        width: mainContent.width
        height: mainContent.height

    }

    FastBlur
    {
        id: msgBlur
        opacity: 0
        anchors.fill: flipableMainWindow
        source: flipableMainWindow
        width: mainContent.width
        height: mainContent.height
        radius: 80

        onOpacityChanged:
        {
            visible = msgBlur.opacity === 0 ? false : true
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
}
