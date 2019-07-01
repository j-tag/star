import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

// Main page handler
import "../Main.js" as Main

GlassMessage {
    // Note: width and height must be set by caller

    property int modelId: -1
    property string title: ""
    property string description: ""
    property var triggerDate: null
    property var triggerTime: null
    property var createdAt: null
    property var updatedAt: null

    Connections {
        target: todayTasks
        onEditTaskResult: {
            // id -> int
            // result -> bool

            closeOverlay()
            msg.close()

            if(result === true) {
                // Edit was successful
            } else {
                // Edit were failed
                Main.showMessage("ویرایش موفقیت آمیز نبود")
            }
        }
    }

    contentItem: Item {
        id: mainLayout
        anchors.fill: parent

        ColumnLayout {
            id: layoutMain
            anchors.fill: parent

            Flickable {
                id: flickable

                Layout.fillHeight: true
                Layout.fillWidth: true
                contentHeight: layout.height + 10
                clip: true

                ColumnLayout {
                    id: layout
                    width: parent.width

                    Text {
                        Layout.fillWidth: true
                        Layout.rightMargin: 30
                        text: qsTr("*فقط فیلد عنوان یادآوری اجباریست، بقیه اختیاری هستند")
                        font.italic: true
                        font.pointSize: 8
                        color: "grey"
                    }

                    Label
                    {
                        Layout.fillWidth: true
                        Layout.topMargin: 20
                        Layout.rightMargin: 30
                        Layout.leftMargin: 30
                        text: qsTr("عنوان یادآوری:")
                        color: Main.textColor
                    }

                    TextField {
                        id: textTitle
                        Layout.fillWidth: true
                        Layout.topMargin: 10
                        Layout.rightMargin: 30
                        Layout.leftMargin: 30
                        placeholderText: qsTr("عنوان یادآوری را در اینجا وارد کنید")
                        color: Main.textColor
                        font.pointSize: 12
                        selectByMouse: true
                    }

                    Label
                    {
                        Layout.fillWidth: true
                        Layout.topMargin: 20
                        Layout.rightMargin: 30
                        Layout.leftMargin: 30
                        text: qsTr("توضیحات:")
                        color: Main.textColor
                    }

                    TextArea {
                        id: textDescription
                        Layout.fillWidth: true
                        Layout.topMargin: 10
                        Layout.rightMargin: 30
                        Layout.leftMargin: 30
                        placeholderText: qsTr("توضیحات بیشتر در مورد یادآوری را در اینجا وارد کنید")
                        color: Main.textColor
                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        selectByMouse: true
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        Layout.topMargin: 20
                        Layout.rightMargin: 30
                        Layout.leftMargin: 30

                        TextField {
                            id: textTriggerTime
                            placeholderText: qsTr("مثال: 12:00:00")
                            color: Main.textColor
                            selectByMouse: true
                            validator: RegExpValidator { regExp: /(?:[01]\d|2[0123]):(?:[012345]\d):(?:[012345]\d)/ }
                        }

                        Label
                        {
                            Layout.rightMargin: 10
                            text: qsTr("ساعت:")
                            color: Main.textColor
                        }

                        Item {
                            Layout.fillWidth: true
                        }

                        TextField {
                            id: textTriggerDate
                            Layout.minimumWidth: 140
                            placeholderText: qsTr("مثال: 1400/03/05")
                            color: Main.textColor
                            selectByMouse: true
                            validator: RegExpValidator { regExp: /([12]\d{3}\/(0[1-9]|1[0-2])\/(0[1-9]|[12]\d|3[01]))/ }
                        }

                        Label
                        {
                            text: qsTr("تاریخ:")
                            color: Main.textColor
                        }
                    }
                }

                ScrollBar.vertical: ScrollBar { }

            }
            Rectangle {
                Layout.fillWidth: true
                height: 2
                color: "#aaa"
            }
            RowLayout {
                Layout.fillWidth: true

                Label {
                    id: labelError
                    color: "red"
                    Layout.fillWidth: true
                }

                Button {
                    Layout.rightMargin: 10
                    flat: true
                    text: qsTr("بستن")

                    onClicked: msg.close()
                }

                Button {
                    Layout.rightMargin: 10
                    flat: true
                    text: qsTr("ثبت تغییرات")
                    highlighted: true

                    onClicked: {

                        const finalTriggerDate = textTriggerDate.acceptableInput ? textTriggerDate.text : textTriggerDate.text.trim().length === 0 ? -1 : "error"

                        const finalTriggerTime = textTriggerTime.acceptableInput ? textTriggerTime.text : textTriggerTime.text.trim().length === 0 ? "" : "error"

                        if(finalTriggerDate === "error") {
                            // Show message about date error
                            showError("تاریخ وارد شده اشتباه است")
                            console.warn("Invalid date value.")
                            return
                        }

                        if(finalTriggerTime === "error") {
                            // Show message about time error
                            showError("ساعت وارد شده اشتباه است")
                            console.warn("Invalid time value.")
                            return
                        }

                        showOverlay()

                        Main.editTask(modelId, textTitle.text.trim(), textDescription.text.trim(),
                                      finalTriggerDate, finalTriggerTime)

                    }
                }
            }
        }

        // Overlay
        Rectangle {
            id: rectOverlay
            anchors.fill: layoutMain
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

    function placeTextFieldValues() {
        textTitle.text = title
        textDescription.text = description
        textTriggerDate.text = triggerDate ? Main.persianNumberToEnglish(jalaliDate.unixTimestampToJalali(triggerDate)) : ""
        textTriggerTime.text = Main.persianNumberToEnglish(triggerTime)
    }

    function showError(message) {
        labelError.text = message
    }
}
