import QtQuick

Column {
    anchors.fill: parent

    DeviceList {
        id: deviceList
        visible: bluetoothManager.connectionState !== 5
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

