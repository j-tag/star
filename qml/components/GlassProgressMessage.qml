import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

// Main page handler
import "../Main.js" as Main

GlassMessage {
    // Note: width and height must be set by caller

    contentItem: Item {
        Text
        {
            id: textMsg
            text: qsTr("در حال ورود به حساب کاربری شما در پیورسافت ...")
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.margins: 14
            bottomPadding: 40
            font.pixelSize: 14
            wrapMode: Text.WordWrap
        }

        BusyIndicator {
            id: busyIndicator
            anchors {
                horizontalCenter: parent.horizontalCenter
                bottomMargin: 14
                bottom: parent.bottom
            }
            running: true
        }
    }

}
