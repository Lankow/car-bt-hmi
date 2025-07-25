import QtQuick 2.15
import CustomControls 1.0

Rectangle {
    color: "transparent"
    width: parent.width
    height: 50

    Text {
        id: stateText
        font.family: "Orbitron"
        font.pixelSize: 15
        color: "#cfcccc"
        anchors{
            verticalCenter: parent.verticalCenter
            left: parent.left
            leftMargin: 10
        }
        text: stateIndicator.stateText + (
                  (bluetoothManager.connectionState === 2 || bluetoothManager.connectionState === 3)
                  && bluetoothManager.activeDeviceName !== ""
                  ? "\n" + bluetoothManager.activeDeviceName
                  : ""
                  )
        elide: Text.ElideRight
        wrapMode: Text.NoWrap
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
