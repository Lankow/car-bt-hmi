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
            text: "Cancel"
            onClicked: bluetoothManager.stopDiscovery()
        }

        DeviceList{}

        Button {
            text: "Send '01 0D'"
            enabled: bluetoothManager.connected
            onClicked: bluetoothManager.sendMessage("010D")
        }

        Button {
            text: "Send '01 0C'"
            enabled: bluetoothManager.connected
            onClicked: bluetoothManager.sendMessage("01 0C")
        }

        Button {
            text: "Send Multiple"
            enabled: bluetoothManager.connected
            onClicked: bluetoothManager.sendMessage("01 0C \r 010D")
        }

        Button {
            text: "Send 'VER'"
            enabled: bluetoothManager.connected
            onClicked: bluetoothManager.sendMessage("VER")
        }
    }
}
