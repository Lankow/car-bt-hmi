import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 400
    height: 600
    title: "Bluetooth Devices"

    // Button {
    //     text: "Start Scan for OBD Device."
    //     onClicked: bluetoothManager.startDiscovery()
    // }

    DeviceList{}
}
