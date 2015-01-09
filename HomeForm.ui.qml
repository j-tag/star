import QtQuick 2.4
import QtQuick.Layouts 1.1
import "Main.js" as Main

Item {

    property alias flickableHome: flickableHome
    property alias rectBg: rectBg

    id: home
    width: mainWindow.width/1.2
    height: 400
    Layout.minimumWidth: 400
    Layout.minimumHeight: 400



    Flickable {
        id: flickableHome
        transformOrigin: Item.Center
        anchors.centerIn: parent
        width: home.width/1.21
        height: 401
        contentHeight: itemHome.height
        contentWidth: itemHome.width


        Rectangle
        {
            id: rectBg
            color: Main.pageColor
            anchors.fill: itemHome

            radius: 3
            opacity: .7

        }


        Item
        {
            id:itemHome
            anchors.centerIn: parent
            width: home.width/1.2
            height: 400


            Row {
                id: rowHome
                width: itemHome.width/1.2
                height: 200
                spacing: 2
                anchors.centerIn: parent

                BirthTimes {
                    id: birthTimesHome
                    width: rowHome.width/2
                    height: 200
                }


                Today {
                    id: todayHome
                    width:rowHome.width/2
                    height: 200
                }
            }
        }
    }
}
