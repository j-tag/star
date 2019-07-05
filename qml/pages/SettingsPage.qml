import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import "../Main.js" as Main

Item {

    id: mainItem

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
                Main.showToast("تنظیمات شما با موفقیت در حساب کاربریتان در پیورسافت ذخیره شد")
            } else {
                // Failed to update settings
                alerts.showErrorMessage("متاسفیم! اما نتوانستیم تنظیمات شما را در پیورسافت ذخیره کنیم. لطفاً مجدداً تلاش کنید و در صورت بر طرف نشدن مشکل با پشتیبانی پیورسافت تماس حاصل فرمایید")
            }

            buttonSave.enabled = true
            closeOverlay()
        }
    }

    Connections {
        target: userDetails

        onNameChanged: textName.text = userDetails.name

        onBirthdayChanged: {

            const birthday = userDetails.birthday

            comboYear.currentIndex = comboYear.find(Main.englishNumberToPersian(jalaliDate.getJalaliYear(userDetails.birthday)))

            comboMonth.currentIndex = parseInt(Main.persianNumberToEnglish(jalaliDate.getJalaliMonth(userDetails.birthday))) - 1

            comboDay.currentIndex = comboDay.find(Main.englishNumberToPersian(jalaliDate.getJalaliDayInMonth(userDetails.birthday)))
        }

        onShowBirthVariantsChanged: checkBoxShowBirthVariants.checked = userDetails.showBirthVariants

        onCelebrateBirthdayChanged: checkBoxCelebrateBirthday.checked = userDetails.celebrateBirthday

        onAutoStartChanged: checkboxAutoStart.checked = userDetails.autoStart

    }

    Layout.minimumWidth: 200
    Layout.minimumHeight: 200

    Flickable {
        id: flickableSettings
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
                        id: checkBoxShowBirthVariants
                        Layout.fillWidth: true
                        text: qsTr("نمایش سن شما به ثانیه و ...")
                    }

                    CheckBox {
                        id: checkBoxCelebrateBirthday
                        Layout.fillWidth: true
                        text: qsTr("تبریک گفتن روز تولد")
                    }

                    CheckBox {
                        id: checkboxAutoStart
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
                                  days[i] = Main.englishNumberToPersian(((i + 1) + "").padStart(2, '0'))
                                }

                                model = days
                            }

                        }

                    }

                    // Save button
                    Button {
                        id: buttonSave

                        Layout.alignment: Qt.AlignCenter
                        Layout.topMargin: 20
                        text: qsTr("ذخیره‌ی تنظیمات")
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
                                        showBirthVariants: checkBoxShowBirthVariants.checked,
                                        celebrateBirthday: checkBoxCelebrateBirthday.checked
                                    },
                                app: {
                                        windows: {
                                            autoStart: checkboxAutoStart.checked
                                        }
                                    }
                                }

                            settings.setOnlineValue(JSON.stringify(json))

                        }
                    }
                }
            }
        }
    }

    Rectangle {
        id: rectOverlay
        anchors.fill: parent
        visible: opacity !== 0
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
        flickableSettings.enabled = false
        rectOverlay.opacity = 1
        busyIndicator.running = true
    }

    function closeOverlay() {
        flickableSettings.enabled = true
        rectOverlay.opacity = 0
        busyIndicator.running = false
    }

}
