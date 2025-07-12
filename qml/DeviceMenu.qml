import QtQuick 2.15

Column {
    anchors.fill: parent

    DeviceList {
        id: deviceList
    }

    Component.onCompleted: {
        bluetoothManager.startDiscovery()
    }

    Component.onDestruction: {
        bluetoothManager.stopDiscovery()
        bluetoothManager.clearResults()
    }
}

