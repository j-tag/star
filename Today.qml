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
            minimumValue: 1
            maximumValue: 365
            value: 114
        }


        Text {
            text: qsTr("زمان سپری شده از این ماه")
        }

        ProgressBar
        {
            id: progMonth
            minimumValue: 1
            maximumValue: 31
            value: 8
        }
    }


}
