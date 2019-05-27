import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.12

Item {

    id: itemToday

    ColumnLayout
    {
        anchors.fill: itemToday
        spacing: 2

        Text {
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
            text: qsTr("زمان سپری شده از امسال")
        }

        ProgressBar
        {
            id: progYear
            Layout.fillWidth: true
            from: 1
            to: 365

            value: jalaliDate.getCurrentJalaliDayInYear()
        }


        Text {
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
            text: qsTr("زمان سپری شده از این ماه")
        }

        ProgressBar
        {
            id: progMonth
            Layout.fillWidth: true
            from: 1
            to: 31

            value: jalaliDate.getCurrentJalaliDayInMonth()
        }

        Text {
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
            text: qsTr("زمان سپری شده از امروز")
        }

        ProgressBar
        {
            id: progDay
            Layout.fillWidth: true
            from: 1
            to: 86400000

            value: jalaliDate.getCurrentMillisecondOfDay()
        }
    }


}
