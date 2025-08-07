import QtQuick
import CustomControls 1.0
import ConnectionState 1.0

Rectangle {
    color: "#292828"
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
                  (bluetoothManager.connectionState === ConnectionState.Connecting || bluetoothManager.connectionState === ConnectionState.Connected)
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
