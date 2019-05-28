import QtQuick 2.7
import QtQuick.Controls 2.12

// Main page handler
import "../Main.js" as Main

GlassMessage {
    // Note: width and height must be set by caller
    property string strMessage

    contentItem: Item {
        Text
        {
            id: textMsg
            text: strMessage
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.margins: 14
            bottomPadding: 40
            font.pixelSize: 14
            wrapMode: Text.WordWrap
        }

        Button
        {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 14
            anchors.bottom: parent.bottom

            text: qsTr("تایید")

            onClicked:msg.close()
        }
    }

}
