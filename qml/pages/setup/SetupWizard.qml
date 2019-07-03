import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../../Main.js" as Main

Item {

    property bool active: false

    Connections {
        target: settings

        onOnlineSettingsUpdated: {

            if(!active) {
                return
            }

            // result -> bool
            // newSettings -> QString (JSON string)

            if(result) {
                // Settings updated successfully
                Main.toggleFlipToMainContent()
            } else {
                // Failed to update settings

                alerts.showErrorMessage("متاسفیم! اما نتوانستیم تنظیمات شما را در پیورسافت ذخیره کنیم. لطفاً مجدداً تلاش کنید و در صورت بر طرف نشدن مشکل با پشتیبانی پیورسافت تماس حاصل فرمایید")

                buttonSave.enabled = true
            }

            closeOverlay()
        }
    }

    Rectangle
    {
        anchors.fill: parent
        color: "#2197d7"
    }

    ColumnLayout {
        anchors {
            top: parent.top
            right: parent.right
            left: parent.left
        }

        Label {
            id: labelMain
            Layout.fillWidth: true
            Layout.topMargin: 40
            text: qsTr("از اینکه نرم افزار ستاره را انتخاب کردید از شما متشکریم! لطفاً اطلاعات خود را وارد کنید تا ستاره برای شما شخصی‌سازی شود")
            color: "#fff"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.WordWrap
        }

        TextField {
            id: textName
            Layout.preferredWidth: 300
            Layout.alignment: Qt.AlignCenter
            Layout.topMargin: 40
            horizontalAlignment: Text.AlignHCenter
            placeholderText: qsTr("نام شما")
            selectByMouse: true
        }

        Text {
            id: textBirthDate
            Layout.alignment: Qt.AlignCenter
            Layout.topMargin: 40
            text: qsTr("تاریخ تولد شما")
            color: "#fff"
            font.pointSize: 14
        }

        RowLayout {
            Layout.alignment: Qt.AlignCenter
            Layout.topMargin: 40

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

        Button {
            id: buttonSave

            Layout.alignment: Qt.AlignCenter
            Layout.topMargin: 40
            text: qsTr("شروع")
            onClicked: {

                enabled = false
                showOverlay()

                const year = Main.persianNumberToEnglish(comboYear.currentText)
                const month = Main.persianNumberToEnglish(comboMonth.currentIndex + 1)
                const day = Main.persianNumberToEnglish(comboDay.currentIndex + 1)

                // Save settings in Pure account
                const json = {
                    user: {
                            name: textName.text,
                            birthday: jalaliDate.jalaliToUnixTimestamp(year, month, day),
                            showBirthVariants: true,
                            celebrateBirthday: true
                        },
                    app: {
                            windows: {
                                autoStart: false
                            }
                        }
                    }

                settings.setOnlineValue(JSON.stringify(json))

            }
        }
    }

    Rectangle {
        id: rectOverlay
        anchors.fill: parent
        visible: false
        opacity: 0
        color: "#903d0d6f"

        BusyIndicator {
            id: busyIndicator
            anchors.centerIn: parent
            running: true
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
        rectOverlay.visible = true
        rectOverlay.opacity = 1
        busyIndicator.running = true
    }

    function closeOverlay() {
        rectOverlay.opacity = 0
        busyIndicator.running = false
    }

}
