import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

// Main page handler
import "../Main.js" as Main

GlassMessage {
    // Note: width and height must be set by caller
    property int modelId: -1
    property string strTitle

    Connections {
        target: todayTasks
        onDeleteTaskResult: {
            // id -> int
            // result -> bool

            closeOverlay()
            msg.close()

            if(result === true) {
                // Delete was successful
            } else {
                // Delete were failed
                Main.showMessage("حذف موفقیت آمیز نبود")
            }
        }
    }

    contentItem: Item {
        id: mainLayout
        anchors.fill: parent

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 14

            Text
            {
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: qsTr("آیا برای حذف این نوت اطمینان دارید؟")
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pointSize: 12
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            }

            Text
            {
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: strTitle
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pointSize: 14
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            }

            RowLayout {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignRight

                Button
                {
                    highlighted: true
                    text: qsTr("حذف نوت")
                    onClicked: {
                        showOverlay()
                        Main.deleteTask(modelId)
                    }
                }

                Button
                {
                    text: qsTr("لغو")
                    onClicked: msg.close()
                }
            }
        }

        // Overlay
        Rectangle {
            id: rectOverlay
            anchors.fill: mainLayout
            visible: opacity !== 0
            opacity: 0
            color: "#903d0d6f"

            BusyIndicator {
                id: busyIndicator
                anchors.centerIn: parent
                running: false
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

    // Functions

    function showOverlay() {
        mainLayout.enabled = false
        busyIndicator.running = true
        rectOverlay.opacity = 1
    }

    function closeOverlay() {
        mainLayout.enabled = true
        busyIndicator.running = false
        rectOverlay.opacity = 0
    }
}
