import QtQuick 2.7
import QtQuick.Controls 2.12
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtGraphicalEffects 1.0
import "components"
import "pages"


// Main page js file
import "Main.js" as Main

ApplicationWindow {
    id: mainWindow
    title: qsTr("نرم افزار تقویم شمسی ستاره")
    width: 740
    height: 480
    minimumWidth: 600
    minimumHeight: 480
    visible: true

    // Main application font
    FontLoader {
        id: appFont
        source: "qrc:/fonts/IRANSans.ttf"
    }

    header: ToolBar
    {

        Row
        {

            ToolButton
            {
                id:toolBtnHome
                text: qsTr("Home")

                onClicked:
                {
                    stack.replace(home)

                    Main.disablePages(home)
                    Main.changeBackground()
                }
            }

            ToolButton
            {
                id:toolBtnTodayHolidays
                text: qsTr("Today Holidays")

                onClicked:
                {
                    stack.replace(todayHolidays)

                    Main.disablePages(todayHolidays)
                    Main.changeBackground()
                }
            }

            ToolButton
            {
                id:toolBtnTodayEvents
                text: qsTr("Today Events")

                onClicked:
                {
                    stack.replace(todayEvents)

                    Main.disablePages(todayEvents)
                    Main.changeBackground()
                }

            }

            ToolButton
            {
                id:toolBtnMsgTest
                text: qsTr("Msg TEST")

                onClicked:
                {
                    Main.showMessage("تاریخ شمسی امروز: " + jalaliDate.getCurrentJalaliDate())
                }

            }

            ToolButton
            {
                id:toolBtnFlipTest
                text: qsTr("Flip TEST")

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
            source: "qrc:/images/background.png"
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
            source: "qrc:/images/background2.png"
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
            source: "qrc:/images/background3.png"
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


        // Stack view used for navigating in pages
        StackView {
            id: stack
            initialItem: home
            anchors.fill: parent

            pushEnter: stackViewTransitionEnter
            pushExit: stackViewTransitionExit
            popEnter: stackViewTransitionEnter
            popExit: stackViewTransitionExit
            replaceEnter: stackViewTransitionEnter
            replaceExit: stackViewTransitionExit
        }

        // Stack view exit transition
        Transition {
            id: stackViewTransitionExit
            PropertyAnimation {
                easing.type: Main.pageEasingType
                properties: "opacity"
                from: 1
                to:0
                duration: Main.pageDuration
            }
            PropertyAnimation {
                easing.type: Main.pageEasingType
                properties: "scale"
                from: 1
                to: 2
                duration: Main.pageDuration
            }
        }

        // Stack view enter transition
        Transition {
            id: stackViewTransitionEnter
            PropertyAnimation {
                easing.type: Main.pageEasingType
                properties: "opacity,scale"
                from: 0
                to: 1
                duration: Main.pageDuration
            }
        }

        // Home page
        Home
        {
            id: home
        }


        // Today holidays page
        TodayHolidays
        {
            id: todayHolidays
            visible: false
        }

        // Today events page
        TodayEvents
        {
            id: todayEvents
            visible: false
        }

    }


    SimpleTextGlassMessage
    {
        id: glassMessage
        opacity: 0
        z: 114// Brings messagebox to top
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
