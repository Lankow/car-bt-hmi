import QtQuick 2.15

Column {
    anchors.fill: parent

    DeviceList{
        id: deviceList
        width: parent.width
    }

    Component.onDestruction: {
        bluetoothManager.stopDiscovery()
        bluetoothManager.clearResults()
    }
}

