import QtQuick 2.7
import QtQuick.Layouts 1.1
import "Main.js" as Main

Item {

    property alias flickableHome: flickableHome
    property alias rectBg: rectBg

    id: home
    width: mainWindow.width/1.2
    height: mainWindow.height/1.2
    Layout.minimumWidth: 200
    Layout.minimumHeight: 200



    Flickable {
        id: flickableHome
        transformOrigin: Item.Center
        anchors.centerIn: parent
        width: home.width/1.21
        height: home.height/1.21
        contentHeight: itemHome.height
        contentWidth: itemHome.width


        Rectangle
        {
            id: rectBg
            color: Main.pageColor
            anchors.fill: itemHome

            radius: Main.pageRadius
            opacity: Main.pageOpacity

        }


        Item
        {
            id:itemHome
            anchors.centerIn: parent
            width: home.width/1.2
            height: home.height/1.3


            Row {
                id: rowHome
                width: itemHome.width/1.2
                height: itemHome.height/1.1
                spacing: 2
                anchors.centerIn: parent

                BirthTimes {
                    id: birthTimesHome
                    width: rowHome.width/2
                    height: rowHome.height/2
                    anchors.verticalCenter: rowHome.verticalCenter
                }


                Today {
                    id: todayHome
                    width:rowHome.width/2
                    height: rowHome.height/2
                    anchors.verticalCenter: rowHome.verticalCenter
                }
            }
        }
    }
}
