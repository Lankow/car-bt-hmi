import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: menu
    width: 250
    height: parent.height
    color: "#292828"

    property bool opened: false

    MenuHeader{
        id: menuHeader
        anchors.top: parent.top
        anchors.left: parent.left
    }

    Loader {
        id: menuLoader
        width:parent.width
        anchors.top: menuHeader.bottom
        sourceComponent: mainMenuComponent

        onLoaded: {
            if (sourceComponent === deviceMenuComponent) {
                bluetoothManager.startDiscovery()
            }
        }
    }

    Component {
        id: mainMenuComponent
        Column {
            anchors.fill: parent
            MenuButton{
                id: deviceButton
                buttontext: "Device"

                MouseArea{
                    anchors.fill: parent
                    onClicked: switchMenu(deviceButton.buttontext, deviceMenuComponent, "back-left")
                }
            }

            MenuButton{
                id: settingsButton
                buttontext: "Settings"

                MouseArea{
                    anchors.fill: parent
                    onClicked: switchMenu(settingsButton.buttontext, settingsMenuComponent, "back-left")
                }
            }

            MenuButton{
                id: helpButton
                buttontext: "Help"
            }
        }
    }

    Component {
        id: deviceMenuComponent


        Column {
            anchors.fill: parent

            DeviceList{
                id:deviceList
                width: parent.width
            }

            Component.onDestruction: {
                bluetoothManager.stopDiscovery()
                bluetoothManager.clearResults()
            }
        }
    }

    Component {
        id: settingsMenuComponent

        Column {
            Label { text: "Settings here..." }
        }
    }

    Behavior on x { NumberAnimation { duration: 300; easing.type: Easing.InOutQuad } }

    function showMenu() {
        menuLoader.sourceComponent = mainMenuComponent
        menuHeader.headerTitle = "CAR-BT-HMI"
        menuIcon.state = "close"
        opened = true
        x = parent.width - width
    }

    function hideMenu() {
        x = parent.width;
        opened = false
        menuIcon.state = "menu"
    }

    function switchMenu(newTitle, newComponent, newIcon) {
        menuHeader.headerTitle = newTitle
        menuLoader.sourceComponent = newComponent
        menuIcon.state = newIcon
    }
}
