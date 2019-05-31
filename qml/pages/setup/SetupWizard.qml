import QtQuick 2.7
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {

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
        }

        RowLayout {
            Layout.alignment: Qt.AlignCenter
            Layout.topMargin: 40

            ComboBox {
                // TODO: Add rest
                model: ["۱", "۲", "۳"]
            }

            ComboBox {
                // TODO: Add rest
                model: ["فروردین", "اردیبهشت", "خرداد"]
            }

            ComboBox {
                // TODO: Add rest
                model: ["1300", "1301", "1302"]
            }

        }

        Button {
            Layout.alignment: Qt.AlignCenter
            Layout.topMargin: 40
            text: qsTr("شروع")
            onClicked: {
                // TODO: Save settings and reload them and start using them
            }
        }
    }


}
