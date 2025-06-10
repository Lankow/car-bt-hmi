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
                    onClicked: {
                        menuHeader.headerTitle = deviceButton.buttontext
                        menuLoader.sourceComponent = deviceMenuComponent
                        menuIcon.state = "back-left"
                    }
                }
            }
        }
    }

    Component {
        id: deviceMenuComponent

        Column {
            anchors.fill: parent
            MenuButton{
                id: scanButton
                buttontext: "Scan Button"

                MouseArea{
                    anchors.fill: parent
                    onClicked: bluetoothManager.startDiscovery()
                }
            }
            MenuButton{
                id: cancelButton
                buttontext: "Cancel Scan"

                MouseArea{
                    anchors.fill: parent
                    onClicked: bluetoothManager.stopDiscovery()
                }
            }
            DeviceList{
                id:deviceList
                width: parent.width
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
        menuIcon.state = "close"
        opened = true
        x = parent.width - width
    }

    function hideMenu() {
        menuIcon.state = "menu"
        x = parent.width;
        opened = false
        menuHeader.headerTitle = "CAR-BT-HMI"
        menuLoader.sourceComponent = mainMenuComponent
    }
}
