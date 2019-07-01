import QtQuick 2.12
import QtGraphicalEffects 1.0

// Main page handler
import "../Main.js" as Main

Item {
    // Note: Geometry must be set by caller

    id: mainItem

    property string strMessage
    property int interval: 10000

    state: "hidden"

    Timer {
        id: timerVisibility
        running: false
        repeat: false
        interval: mainItem.interval

        onTriggered: close()
    }

    Rectangle {
        id: rectToastBackground
        anchors.fill: fastBlur
        color: "white"
        radius: 40
        clip: true
    }

    DropShadow {
        anchors.fill: rectToastBackground
        horizontalOffset: 0
        verticalOffset: 0
        radius: 18.0
        samples: 37 // Radius * 2 + 1
        color: "#85333333"
        source: rectToastBackground
    }

    FastBlur {
        id: fastBlur

        width: textToast.width
        height: textToast.height
        x: textToast.x
        y: textToast.y
        clip: true

        radius: 40
        opacity: 0.85

        layer.enabled: true
        layer.effect: OpacityMask {
            maskSource: rectToastBackground
        }

        source: ShaderEffectSource {
            sourceItem: mainContent
            sourceRect: Qt.rect(fastBlur.x, fastBlur.y, fastBlur.width, fastBlur.height)
        }
    }

    Text {
        id: textToast
        width: 400
        anchors {
            horizontalCenter: mainItem.horizontalCenter
            bottom: mainItem.bottom
            bottomMargin: 100
        }
        topPadding: 14
        bottomPadding: 14
        rightPadding: 10
        leftPadding: 10
        text: strMessage
        color: Main.textColor
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
    }

    states: [
        State {
            name: "normal"
            AnchorChanges {
                target: textToast
                anchors.bottom: mainItem.bottom
                anchors.top: undefined
            }
        },
        State {
            name: "hidden"
            AnchorChanges {
                target: textToast
                anchors.top: mainItem.bottom
                anchors.bottom: undefined
            }
        }
    ]

    transitions: Transition {
        AnchorAnimation { duration: 850; easing.type: Easing.InOutBack }
    }

    // Functions

    function show() {
        timerVisibility.start()
        mainItem.state ="normal"
    }

    function close() {
        mainItem.state ="hidden"
    }

}
