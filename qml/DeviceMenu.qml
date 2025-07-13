import QtQuick 2.15

Column {
    anchors.fill: parent

    DeviceList {
        id: deviceList
        width: parent.width
    }

    Component.onCompleted: {
        bluetoothManager.startDiscovery()
    }

    Component.onDestruction: {
        bluetoothManager.stopDiscovery()
        bluetoothManager.clearResults()
    }
}

