import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: menu
    width: 200
    color: "#ffffff"
    visible: false

    // TODO: Attach values to DataProvider


    Column {
        id: menuContent
        anchors.fill: parent
        spacing: 10
        padding: 10

        // Default Menu Page
        Loader {
            id: menuLoader
            sourceComponent: mainMenuComponent
        }
    }

    Component {
        id: mainMenuComponent

        Column {
            spacing: 10

            Button {
                text: "Device"
                onClicked: menuLoader.sourceComponent = deviceMenuComponent
            }

            Button {
                text: "Settings"
                onClicked: menuLoader.sourceComponent = settingsMenuComponent
            }
        }
    }

    Component {
        id: deviceMenuComponent

        Column {
            spacing: 10

            Button {
                text: "< Back"
                onClicked: menuLoader.sourceComponent = mainMenuComponent
            }

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
    }

    Component {
        id: settingsMenuComponent

        Column {
            spacing: 10

            Button {
                text: "< Back"
                onClicked: menuLoader.sourceComponent = mainMenuComponent
            }

            Label { text: "Settings here..." }
        }
    }

    function showMenu() {
        visible = true
        x = parent.width - width
    }

    function hideMenu() {
        x = parent.width
        menuLoader.sourceComponent = mainMenuComponent
        visible = false
    }
}
