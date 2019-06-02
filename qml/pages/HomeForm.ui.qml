import QtQuick 2.7
import QtQuick.Layouts 1.3
import "../Main.js" as Main

Item {

    property alias flickableHome: flickableHome
    property alias rectBg: rectBg
    property alias textName: textName

    id: home
    Layout.minimumWidth: 200
    Layout.minimumHeight: 200

    Flickable {
        id: flickableHome
        transformOrigin: Item.Center
        anchors.centerIn: parent
        width: home.width / 1.21
        height: home.height / 1.21
        contentHeight: itemHome.height
        contentWidth: itemHome.width

        Rectangle {
            id: rectBg
            color: Main.pageColor
            anchors.fill: itemHome

            radius: Main.pageRadius
            opacity: Main.pageOpacity
        }

        Item {
            id: itemHome
            anchors.centerIn: parent
            width: home.width / 1.2
            height: home.height / 1.3

            Text {
                id: textName
                anchors.horizontalCenter: parent.horizontalCenter
                topPadding: 20
                font.pointSize: 14
            }

            Row {
                id: rowHome
                width: itemHome.width / 1.2
                height: itemHome.height / 1.1
                spacing: 2
                anchors.centerIn: parent

                BirthTimes {
                    id: birthTimesHome
                    width: rowHome.width / 2
                    height: rowHome.height / 1.5
                    anchors.verticalCenter: rowHome.verticalCenter
                }

                Today {
                    id: todayHome
                    width: rowHome.width / 2
                    height: rowHome.height / 1.5
                    anchors.verticalCenter: rowHome.verticalCenter
                }
            }
        }
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
