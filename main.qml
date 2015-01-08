import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtGraphicalEffects 1.0

// Jalalidate handler
import PureSoft.JalaliDate.currentJalaliDate 1.0 as JalaliDate

// Main page js file
import "Main.js" as Main
import "JalaliDate.js" as JDate

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
                text: qsTr("خانه")
                iconSource: "qrc:/Images/toolbar-home.png"
                tooltip: text


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
                text: qsTr("مناسبت های امروزز")
                iconSource: "qrc:/Images/toolbar-todayholidays.png"
                tooltip: text

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
                text: qsTr("یادآوری های امروزز")
                iconSource: "qrc:/Images/toolbar-todayevents.png"
                tooltip: text

                onClicked:
                {
                    stack.push(todayEvents)

                    Main.disablePages(todayEvents)
                    Main.changeBackground()

                    //Main.showMessage("YAAAA GOD")
                }

            }

            ToolButton
            {
                id:toolBtnMsgTest
                text: qsTr("MSG TEST")
                tooltip: text

                onClicked:
                {
                    Main.showMessage("YAAAA GOD: " + JDate.getCurrentJalaliDate())
                }

            }
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

    GaussianBlur
    {
        id: msgBlur
        opacity: 0
        anchors.fill: mainContent
        source: mainContent
        width: mainContent.width
        height: mainContent.height
        radius: 8
        samples: 16

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
