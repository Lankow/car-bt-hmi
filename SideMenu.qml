import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: menu
    width: 250
    height: parent.height
    color: "#292828"

    property bool opened: false

    Column {
        id: menuContent
        anchors.fill: parent
        spacing: 15

        Rectangle{
            height: 40
            color: "transparent"
            width: parent.width

            Text{
                text:"CAR-BT-HMI"
                font.family: "Orbitron"
                font.pointSize: 18

                x: 10
                y: 12
                color: "#cfcccc"
            }
        }

        Rectangle{
            width:parent.width
            height: 2
            color: "#cfcccc"
        }

        Text{
            text:"Device"
            font.family: "Orbitron"
            font.pointSize: 14
            x: 10
            color: "#cfcccc"
        }

        Text{
            text:"Settings"
            font.family: "Orbitron"
            font.pointSize: 14
            x: 10
            color: "#cfcccc"
        }

        Text{
            text:"About"
            font.family: "Orbitron"
            font.pointSize: 14
            x: 10
            color: "#cfcccc"
        }

        // Loader {
        //     id: menuLoader
        //     sourceComponent: mainMenuComponent
        // }
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

    Behavior on x { NumberAnimation { duration: 300; easing.type: Easing.InOutQuad } }

    function showMenu() {
        opened = true
        x = parent.width - width
    }

    function hideMenu() {
        x = parent.width;
        opened = false
        menuLoader.sourceComponent = mainMenuComponent
    }
}
