import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: transition
    property Item loadingScreen
    property Item mainContent
    property alias running: transitionTimer.running
    signal onFinished()

    Timer {
        id: transitionTimer
        interval: 1600
        running: false
        repeat: false
        onTriggered: crossFade.start()
    }

    SequentialAnimation {
        id: crossFade

        ParallelAnimation {
            PropertyAnimation {
                target: transition.loadingScreen
                property: "opacity"
                to: 0.0
                duration: 600
                easing.type: Easing.InOutCubic
            }

            PropertyAnimation {
                target: transition.mainContent
                property: "opacity"
                to: 1.0
                duration: 800
                easing.type: Easing.InOutCubic
            }

            PropertyAnimation {
                target: transition.mainContent
                property: "scale"
                to: 1.0
                duration: 800
                easing.type: Easing.OutQuad
            }
        }

        ScriptAction {
            script: transition.onFinished()
        }
    }
}
