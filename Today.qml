import QtQuick 2.7
import QtQuick.Controls 2.0

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
            from: 1
            to: 365

            value: JDate.getCurrentJalaliDayInYear()
        }


        Text {
            text: qsTr("زمان سپری شده از این ماه")
        }

        ProgressBar
        {
            id: progMonth
            width: itemToday.width
            from: 1
            to: 31

            value: JDate.getCurrentJalaliDayInMonth()
        }
    }


}
