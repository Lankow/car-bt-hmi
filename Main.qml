import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 400
    height: 600
    title: "Bluetooth Devices"
    Column{

        Button {
            text: "Start Scan"
            onClicked: bluetoothManager.startDiscovery()
        }
        Button {
            text: "Stop Scan"
            onClicked: bluetoothManager.stopDiscovery()
        }
        DeviceList{}
    }
}
