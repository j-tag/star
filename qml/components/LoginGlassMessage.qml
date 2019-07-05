import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

// Main page handler
import "../Main.js" as Main

GlassMessage {
    // Note: width and height must be set by caller


    Connections {
        target: oauth2
        onLoginResult: {
            // result -> bool
            // strMessage -> QString

            if(result === true) {
                // Login was successful

                // Load settings
                settings.getOnlineSettings()

                // Close login dialog
                msg.close()
            } else {
                // Login were failed
                labelError.text = strMessage
                labelError.visible = true
                flickable.enabled = true
                busyIndicator.running = false
                rectOverlay.opacity = 0
            }
        }
    }

    contentItem: Item {
        anchors.fill: parent

        Flickable {
            id: flickable

            anchors.fill: parent
            contentHeight: layout.height + 40

            ColumnLayout {
                id: layout
                width: parent.width

                Label
                {
                    Layout.fillWidth: true
                    text: qsTr("ورود به حساب کاربری پیورسافت")
                    color: Main.textColor
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    topPadding: 40
                    bottomPadding: 14
                    wrapMode: Text.WordWrap
                }

                Button {
                    Layout.fillWidth: true
                    Layout.rightMargin: 14
                    Layout.leftMargin: 14
                    flat: true
                    text: qsTr("اگر حساب کاربری ندارید اینجا کلیک کنید تا یک حساب کاملاً رایگان را به راحتی ایجاد کنید")
                    onClicked: Qt.openUrlExternally("https://puresoftware.org/go/register")
                }

                TextField
                {
                    id: textUsername
                    Layout.preferredWidth: 200
                    Layout.alignment: Qt.AlignHCenter
                    placeholderText: qsTr("نام کاربری")
                    bottomPadding: 14
                    selectByMouse: true
                }

                TextField
                {
                    id: textPassword
                    Layout.preferredWidth: 200
                    Layout.alignment: Qt.AlignHCenter
                    placeholderText: qsTr("گذرواژه")
                    bottomPadding: 14
                    echoMode: TextInput.Password
                    selectByMouse: true
                }

                Label {
                    id: labelError
                    visible: false
                    Layout.fillWidth: true
                    color: "red"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    wrapMode: Text.WordWrap
                }

                Button
                {
                    text: qsTr("ورود")
                    Layout.alignment: Qt.AlignHCenter
                    onClicked: login()
                }


            }

            ScrollBar.vertical: ScrollBar { }

        }

        // Overlay
        Rectangle {
            id: rectOverlay
            anchors.fill: flickable
            visible: false
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

    function login() {
        flickable.enabled = false
        rectOverlay.visible = true
        busyIndicator.running = true
        rectOverlay.opacity = 1
        oauth2.login(textUsername.text, textPassword.text)
    }
}
