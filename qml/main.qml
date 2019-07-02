import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import QtQuick.Dialogs 1.2
import QtGraphicalEffects 1.0
import "components"
import "pages"
import "pages/setup"


// Main page js file
import "Main.js" as Main

ApplicationWindow {
    id: mainWindow
    title: qsTr("نرم افزار تقویم شمسی ستاره")
    width: 740
    height: 520
    minimumWidth: 600
    minimumHeight: 480
    visible: true

    // Main application font
    FontLoader {
        id: appFont
        source: "qrc:/fonts/IRANSans.ttf"
    }

    Connections {
        target: setup

        onInitSetupWizard: {
            Main.toggleFlipToSetupWizard()
        }
    }

    Connections {

        // This is the entry point of C++ logic
        Component.onCompleted: star.start()

        target: oauth2
        onShowLoginBox: {

            // result -> bool

            if(result) {
                // Here we should show login box
                glassProgressMessage.close()
                Main.showLoginPopup()
            } else {
                // In this case we don't need to show login box
                // So close everything related to login

                loginGlassMessage.close()
                glassProgressMessage.close()
            }
        }
    }

    Connections {
        target: alerts
        onShowError: {

            // strMessage -> string

            glassMessage.close()
            Main.showMessage(strMessage)

        }
    }

    Component.onCompleted: Main.showGlassProgressMessage()


    header: ToolBar
    {
        Row
        {

            ToolButton
            {
                id: toolBtnHome
                text: qsTr("صفحه‌ی اصلی")

                onClicked: Main.changePage(home)
            }

            ToolButton
            {
                id: toolBtnTodayHolidays
                text: qsTr("مناسبت‌های امروز")

                onClicked: Main.changePage(todayHolidays)
            }

            ToolButton
            {
                id: toolBtnTodayTasks
                text: qsTr("یادآوری‌های من")

                onClicked: Main.changePage(todayTasksPage)
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
                id: toolBtnSettings
                text: qsTr("SETTINGS")

                onClicked:
                {
                    Main.showMessage("تنظیمات")
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
        back: setupWizard

        transform: Rotation
        {
            id: rotation
            origin.x: flipableMainWindow.width / 2
            origin.y: flipableMainWindow.height / 2
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

    SetupWizard
    {
        id: setupWizard

        width: mainWindow.width
        height: mainWindow.height
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

        // Today tasks page
        TodayTasks
        {
            id: todayTasksPage
            visible: false
        }

    }

    GlassTaskRemoveQuestion
    {
        id: glassTaskRemoveQuestion
        opacity: 0
        z: 114 // Brings messagebox to top
        anchors.centerIn: mainContent
        width: mainContent.width
        height: mainContent.height
    }

    SimpleTextGlassMessage
    {
        id: glassMessage
        opacity: 0
        z: 114 // Brings messagebox to top
        anchors.centerIn: mainContent
        width: mainContent.width
        height: mainContent.height
    }

    LoginGlassMessage
    {
        id: loginGlassMessage
        opacity: 0
        z: 40 // Brings messagebox to top
        anchors.centerIn: mainContent
        width: mainContent.width
        height: mainContent.height
    }

    GlassTaskCardView
    {
        id: glassTaskCardView
        opacity: 0
        z: 40 // Brings messagebox to top
        anchors.centerIn: mainContent
        width: mainContent.width
        height: mainContent.height
    }

    GlassTaskCardNew
    {
        id: glassTaskCardNew
        opacity: 0
        z: 40 // Brings messagebox to top
        anchors.centerIn: mainContent
        width: mainContent.width
        height: mainContent.height
    }

    GlassTaskCardEdit
    {
        id: glassTaskCardEdit
        opacity: 0
        z: 40 // Brings messagebox to top
        anchors.centerIn: mainContent
        width: mainContent.width
        height: mainContent.height
    }

    GlassProgressMessage
    {
        id: glassProgressMessage
        opacity: 0
        z: 40 // Brings messagebox to top
        anchors.centerIn: mainContent
        width: mainContent.width
        height: mainContent.height
    }

    BlurToastMessage {
        id: blurToastMessage
        anchors.fill: mainContent
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

        onOpacityChanged: visible = msgBlur.opacity === 0 ? false : true

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
