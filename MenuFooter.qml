import QtQuick 2.15
import CustomControls 1.0

Rectangle {
    color: "transparent"
    width: parent.width
    height: 50

    Text {
        id: stateText
        text: stateIndicator.stateText
        font.family: "Orbitron"
        font.pixelSize: 18
        color: "#cfcccc"
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 10
    }


    StateIndicator {
        id: stateIndicator
        size: 30
        connectionState: bluetoothManager.connectionState
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 15
    }
}
