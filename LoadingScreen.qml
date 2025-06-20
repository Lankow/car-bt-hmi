import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: loadingScreenRoot
    anchors.fill: parent
    z: 999
    color: "#000000"
    visible: true
    opacity: 1.0

    Image {
        source: "logo.svg"
        width: 300
        fillMode: Image.PreserveAspectFit
        anchors{
            verticalCenter: parent.verticalCenter
            horizontalCenter: parent.horizontalCenter
        }
    }

    Timer {
        id: hideTimer
        interval: 1500
        running: true
        repeat: false
        onTriggered: fadeOut.start()
    }

    SequentialAnimation {
        id: fadeOut
        PropertyAnimation {
            target: loadingScreenRoot
            property: "opacity"
            to: 0
            duration: 500
            easing.type: Easing.InOutQuad
        }
        ScriptAction {
            script: loadingScreenRoot.visible = false
        }
    }
}
