import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: menu
    width: 200
    color: "#ffffff"
    visible: false
    x: parent.width

    Column {
        id: menuContent
        anchors.fill: parent
        spacing: 10
        padding: 10

        Button {
            text: "Start Scan"
            onClicked: bluetoothManager.startDiscovery()
        }

        Button {
            text: "Cancel"
            onClicked: {
                bluetoothManager.stopDiscovery()
                hideMenu()
            }
        }

        DeviceList{}
    }

    function showMenu() {
        visible = true
    }

    function hideMenu() {
        visible = false
    }
}
