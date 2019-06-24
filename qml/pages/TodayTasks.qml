import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import "../Main.js" as Main

Item {

    id: mainItem

    property int currentPage: todayTasks.currentPage
    property int pageCount: todayTasks.pageCount
    property int lastInteractedIndex: 0

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

    Connections {
        target: todayTasks
        onDeleteTaskResult: {
            // id -> int
            // result -> bool

            closeOverlay()
        }

        onPaginationChanged: {
            // pageCount -> int
            // currentPage -> int

            mainItem.pageCount = pageCount

            closeOverlay()
        }
    }

    Layout.minimumWidth: 200
    Layout.minimumHeight: 200

    Flickable {
        id: flickableTodayEvents
        transformOrigin: Item.Center
        anchors.centerIn: parent
        width: todayTasksPage.width / 1.21
        height: todayTasksPage.height / 1.21
        contentHeight: itemTodayEvents.height
        contentWidth: itemTodayEvents.width

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
            anchors.fill: itemTodayEvents

            radius: Main.pageRadius
            opacity: Main.pageOpacity
        }

        Item {
            id: itemTodayEvents
            anchors.centerIn: parent
            width: todayTasksPage.width / 1.2
            height: todayTasksPage.height / 1.3

            GridView {
                id: gridviewTodayEvents
                width: itemTodayEvents.width / 1.2
                height: itemTodayEvents.height / 1.1
                anchors.fill: parent
                cellWidth: width / Math.floor(width / 200)
                cellHeight: 240
                clip: true
                layoutDirection: Qt.RightToLeft

                model: todayTasks.tasks

                onAtYEndChanged: {
                      if (gridviewTodayEvents.atYEnd) {
                          if(pageCount > currentPage) {
                              // Loading next page ...
                              loadNextPage()
                          }
                      }
                    }

                onCountChanged: gridviewTodayEvents.positionViewAtIndex(Math.min(lastInteractedIndex, gridviewTodayEvents.count - 1), ListView.Center)

                populate: Transition {
                    NumberAnimation { property: "opacity"; from: 0.0; to: 1.0; duration: 500 }
                    NumberAnimation { property: "scale"; easing.type: Easing.OutExpo; from: 0.0; to: 1.0; duration: 750 }
                }

                delegate: Item {
                        width: 200
                        height: 240

                        Rectangle {
                            id: rectCardBg
                            width: 170
                            height: 220
                            anchors.centerIn: parent

                            state: "normal"
                            radius: 10

                            MouseArea {
                                anchors.fill: rectCardBg
                                hoverEnabled: true
                                onEntered: rectCardBg.state = "hover"
                                onExited: rectCardBg.state = "normal"
                                onPressed: rectCardBg.state = "pressing"
                                onReleased: rectCardBg.state = "normal"
                                onClicked: {
                                    Main.showTask(modelData.id, modelData.title, modelData.description,
                                                  modelData.trigger_date, modelData.trigger_time, modelData.created_at, modelData.updated_at)
                                }
                            }

                            ColumnLayout {
                                anchors.fill: parent
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
                                            color: Main.textColor
                                            wrapMode: Text.Wrap
                                            font.bold: true
                                        }
                                        Text {
                                            clip: true
                                            Layout.fillWidth: true
                                            Layout.fillHeight: true
                                            text: modelData.description
                                            color: Main.textColor
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
                                        onClicked: {
                                            showOverlay()
                                            lastInteractedIndex = index
                                            Main.deleteTask(modelData.id)
                                        }
                                    }
                                }
                            }

                            states: [
                                State {
                                    name: "normal"
                                    PropertyChanges { target: rectCardBg; color: "#ffff66" }
                                },
                                State {
                                    name: "hover"
                                    PropertyChanges { target: rectCardBg; color: "#adff2f" }
                                },
                                State {
                                    name: "pressing"
                                    PropertyChanges { target: rectCardBg; color: "#7ecf55" }
                                }
                            ]

                            transitions: Transition {
                                ColorAnimation { target: rectCardBg; duration: Main.pageDuration; easing.type: Main.pageEasingType}
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
            }
        }
    }

    // Overlay
    Rectangle {
        id: rectOverlay
        anchors.fill: mainItem
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

    // Functions

    function showOverlay() {
        mainItem.enabled = false
        busyIndicator.running = true
        rectOverlay.opacity = 1
    }

    function closeOverlay() {
        mainItem.enabled = true
        busyIndicator.running = false
        rectOverlay.opacity = 0
    }

    function loadNextPage() {
        showOverlay()
        console.log("Loading next task page.")
        todayTasks.append(++currentPage)
    }
}
/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
