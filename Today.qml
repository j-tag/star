import QtQuick 2.0
import QtQuick.Controls 1.3

Item {

    id: itemToday

    Column
    {
        anchors.fill: itemToday
        spacing: 2

        Text {
            text: qsTr("زمان سپری شده از امسال")
        }

        ProgressBar
        {
            id: progYear
            width: itemToday.width
            minimumValue: 1
            maximumValue: 365

            value: JDate.getCurrentJalaliDayInYear()
        }


        Text {
            text: qsTr("زمان سپری شده از این ماه")
        }

        ProgressBar
        {
            id: progMonth
            width: itemToday.width
            minimumValue: 1
            maximumValue: 31

            value: JDate.getCurrentJalaliDayInMonth()
        }
    }


}
