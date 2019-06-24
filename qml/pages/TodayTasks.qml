import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import "../Main.js" as Main

TodayTasksForm {

    Connections {
        target: oauth2
        onLoginResult: {
            // result -> bool
            // strMessage -> QString

            if(result === true) {
                // Login was successful
                todayTasks.reload(1)
            }
        }
    }

    gridviewTodayEvents.delegate: Item {
        width: 200
        height: 240

        Rectangle {
            id: rectCardBg
            width: 170
            height: 220
            anchors.centerIn: parent

            color: "yellow"
            radius: 10

            ColumnLayout {
                anchors {
                    fill: parent
                }
                spacing: 0

                Item {
                    Layout.topMargin: 20
                    Layout.rightMargin: 20
                    Layout.leftMargin: 20
                    Layout.bottomMargin: 5
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    ColumnLayout {
                        anchors.fill: parent
                        Text {
                            Layout.fillWidth: true
                            text: (modelData.title + "").slice(0, 85)
                            wrapMode: Text.Wrap
                            font.bold: true
                        }
                        Text {
                            clip: true
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            text: modelData.description
                            wrapMode: Text.Wrap
                        }
                    }
                }
                RowLayout {
                    Layout.fillWidth: true
                    layoutDirection: Qt.RightToLeft
                    Layout.alignment: Qt.AlignRight
                    spacing: 0
                    RoundButton {
                        text: "⋮"
                        flat: true
                        Layout.margins: 0
                        padding: 0
                    }
                    RoundButton {
                        text: "×"
                        flat: true
                        Layout.margins: 0
                        padding: 0
                    }
                }
            }
        }

        DropShadow {
            anchors.fill: rectCardBg
            cached: true
            horizontalOffset: 0
            verticalOffset: 1
            radius: 8.0
            samples: 14
            color: "#85333333"
            source: rectCardBg
        }
    }

    flickableTodayEvents.rebound: Transition {
                           NumberAnimation {
                               properties: "x,y"
                               duration: Main.pageDuration
                               easing.type: Main.pageEasingType
                           }
                       }
}












/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
