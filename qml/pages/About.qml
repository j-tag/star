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
        id: flickableAbout
        transformOrigin: Item.Center
        anchors.centerIn: parent
        width: about.width / 1.21
        height: about.height / 1.21
        contentHeight: itemAbout.height
        contentWidth: itemAbout.width

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
            anchors.fill: itemAbout

            radius: Main.pageRadius
            opacity: Main.pageOpacity
        }

        Item {
            id: itemAbout
            anchors.centerIn: parent
            width: about.width / 1.2
            height: about.height / 1.3

            RowLayout {
                anchors.fill: parent

                ColumnLayout {
                    Layout.fillWidth: true
                    Layout.margins: 14

                    Image {
                        Layout.fillWidth: true
                        source: "qrc:/images/pure-soft-logo.png"
                        fillMode: Image.PreserveAspectFit
                        antialiasing: true
                        smooth: true
                    }
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    Layout.margins: 14

                    Text {
                        Layout.fillWidth: true
                        text: qsTr("از اینکه نرم‌افزار ستاره را انتخاب کردید از شما متشکریم! لطفاً با ارائه‌ی نظرات خود در پشتیبانی پیورسافت ما را برای بهتر کردن ستاره راهنمایی کنید!")
                        color: Main.textColor
                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignRight

                        Button {
                            Layout.minimumWidth: 140
                            Layout.alignment: Qt.AlignRight
                            text: qsTr("راهنمایی ستاره")
                            onClicked: Qt.openUrlExternally("https://puresoftware.org/go/starhelp")
                        }

                        Button {
                            Layout.minimumWidth: 140
                            Layout.alignment: Qt.AlignRight
                            text: qsTr("پشتیبانی پیورسافت")
                            onClicked: Qt.openUrlExternally("https://puresoftware.org/go/support")
                        }

                        Button {
                            Layout.minimumWidth: 140
                            Layout.alignment: Qt.AlignRight
                            text: qsTr("وبسایت پیورسافت")
                            onClicked: Qt.openUrlExternally("https://puresoftware.org")
                        }

                    }

                    Text {
                        Layout.fillWidth: true
                        text: qsTr("استخراج و تنظیم رویداد‌های تقویم: شورای مرکزی تقویم موسسه‌ی ژئوفیزیک دانشگاه تهران - مناسبت‌ها از شورای فرهنگ عمومی")
                        color: Main.textColor
                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    }

                    Text {
                        Layout.fillWidth: true
                        text: qsTr("تولید شده توسط پیورسافت")
                        color: Main.textColor
                    }

                    Text {
                        Layout.fillWidth: true
                        text: "نسخه‌ی " + Main.englishNumberToPersian(star.getAppVersion())
                        color: Main.textColor
                    }
                }
            }
        }
    }
}
