import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import "../Main.js" as Main

Item {

    id: mainItem

    Layout.minimumWidth: 200
    Layout.minimumHeight: 200

    Flickable {
        id: flickableTodayEvents
        transformOrigin: Item.Center
        anchors.centerIn: parent
        width: settingsPage.width / 1.21
        height: settingsPage.height / 1.21
        contentHeight: itemSettings.height
        contentWidth: itemSettings.width

        rebound: Transition {
                NumberAnimation {
                    properties: "x,y"
                    duration: Main.pageDuration
                    easing.type: Main.pageEasingType
                }
            }

        Rectangle {
            id: rectBg
            color: Main.pageColor
            anchors.fill: itemSettings

            radius: Main.pageRadius
            opacity: Main.pageOpacity
        }

        Item {
            id: itemSettings
            anchors.centerIn: parent
            width: settingsPage.width / 1.2
            height: settingsPage.height / 1.3

            ColumnLayout {
                anchors.fill: parent

            }
        }
    }
}
