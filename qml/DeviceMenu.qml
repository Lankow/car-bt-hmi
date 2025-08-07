import QtQuick
import ConnectionState 1.0

Column {
    anchors.fill: parent

    DeviceList {
        id: deviceList
        visible: bluetoothManager.connectionState !== ConnectionState.NotPermitted
        width: parent.width
    }

    MenuTextBlock {
        visible: !deviceList.visible
        text: "Bluetooth encountered a problem. Please make sure the app has Bluetooth permissions and that your Bluetooth adapter is connected and working properly."
    }

    Component.onCompleted: {
        bluetoothManager.startDiscovery()
    }

    Component.onDestruction: {
        bluetoothManager.stopDiscovery()
        bluetoothManager.clearResults()
    }
}

