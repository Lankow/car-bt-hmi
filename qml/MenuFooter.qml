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
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 10

        text: {
            switch (bluetoothManager.connectionState) {
                case 0: return "Not connected";
                case 1: return "Discovering";
                case 2: return bluetoothManager.connectedDeviceName !== ""
                            ? "Connecting to \n" + bluetoothManager.connectedDeviceName
                            : "Connecting";
                case 3: return bluetoothManager.connectedDeviceName !== ""
                            ? "Connected to \n" + bluetoothManager.connectedDeviceName
                            : "Connected";
                case 4: return "Disconnected";
                case 5: return "Error";
                default: return "Unknown";
            }
        }

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
