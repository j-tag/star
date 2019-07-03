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

            RowLayout {
                anchors.fill: parent

                ColumnLayout {
                    Layout.fillWidth: true
                    Layout.margins: 14

                    CheckBox {
                        Layout.fillWidth: true
                        text: qsTr("نمایش سن شما به ثانیه و ...")
                    }
                    CheckBox {
                        Layout.fillWidth: true
                        text: qsTr("تبریک گفتن روز تولد")
                    }
                    CheckBox {
                        Layout.fillWidth: true
                        text: qsTr("شروع به همراه ویندوز")
                    }
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    Layout.margins: 14

                    TextField {
                        id: textName
                        Layout.preferredWidth: 300
                        Layout.alignment: Qt.AlignRight
                        Layout.topMargin: 10
                        horizontalAlignment: Text.AlignHCenter
                        placeholderText: qsTr("نام شما")
                        selectByMouse: true
                    }

                    Text {
                        id: textBirthDate
                        Layout.alignment: Qt.AlignRight
                        Layout.topMargin: 20
                        text: qsTr("تاریخ تولد شما")
                        color: Main.textColor
                        font.pointSize: 14
                    }

                    RowLayout {
                        Layout.alignment: Qt.AlignRight
                        Layout.topMargin: 10

                        ComboBox {

                            id: comboYear

                            Component.onCompleted: {
                                let years = []

                                for (let i = 0; i < 200; i++) {
                                  years[i] = Main.englishNumberToPersian(i + 1300)
                                }

                                model = years
                            }

                        }

                        ComboBox {

                            id: comboMonth

                            model: [
                            "فروردین",
                            "اردیبهشت",
                            "خرداد",
                            "تیر",
                            "مرداد",
                            "شهریور",
                            "مهر",
                            "آبان",
                            "آذر",
                            "دی",
                            "بهمن",
                            "اسفند"
                            ]
                        }

                        ComboBox {

                            id: comboDay

                            Component.onCompleted: {
                                let days = []

                                for (let i = 0; i < 31; i++) {
                                  days[i] = Main.englishNumberToPersian(i + 1)
                                }

                                model = days
                            }

                        }

                    }
                }
            }

        }
    }
}
