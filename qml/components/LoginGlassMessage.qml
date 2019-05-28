import QtQuick 2.7
import QtQuick.Controls 2.12

GlassMessage {
    // Note: width and height must be set by caller

    contentItem: Item {
        Text
        {
            id: textMsg
            text: qsTr("ورود به حساب کاربری پیورسافت")
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

            text: qsTr("ورود")

            onClicked: msg.close()
        }
    }

}
