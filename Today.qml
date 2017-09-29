import QtQuick 2.7
import QtQuick.Controls 2.0

Item {

    id: itemToday

    Column
    {
        anchors.fill: itemToday
        spacing: 2

        Text {
            text: qsTr("Elapsed time of year")
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
            text: qsTr("Time passed from this month")
        }

        ProgressBar
        {
            id: progMonth
            width: itemToday.width
            from: 1
            to: 31

            value: JDate.getCurrentJalaliDayInMonth()
        }

        Text {
            text: qsTr("Elapsed time of today")
        }

        ProgressBar
        {
            id: progDay
            width: itemToday.width
            from: 1
            to: 86400000

            value: JDate.getCurrentMillisecondOfDay()
        }
    }


}
