import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: menu
    width: 250
    height: parent.height
    color: "#292828"
    z: 999
    property bool opened: false

    // === Menu Registry ===
    property var menuRegistry: ({
        main: {
            id: "main",
            header: "CAR-BT-HMI",
            icon: "menu",
            component: mainMenuComponent
        },
        device: {
            id: "device",
            header: "Device",
            icon: "back-left",
            component: deviceMenuComponent
        },
        settings: {
            id: "settings",
            header: "Settings",
            icon: "back-left",
            component: settingsMenuComponent
        }
    })

    MenuHeader {
        id: menuHeader
        anchors.top: parent.top
        anchors.left: parent.left
    }

    Loader {
        id: menuLoader
        width: parent.width
        anchors.top: menuHeader.bottom
        sourceComponent: menuRegistry.main.component

        onLoaded: {
            if (sourceComponent === deviceMenuComponent) {
                bluetoothManager.startDiscovery()
            }

            if (item && item.menuSwitchRequested) {
                item.menuSwitchRequested.connect(switchTo)
            }
        }
    }

    MenuFooter {
        id: menuFooter
        anchors.bottom: parent.bottom
        anchors.left: parent.left
    }

    Component { id: mainMenuComponent; MainMenu {} }
    Component { id: deviceMenuComponent; DeviceMenu {} }
    Component { id: settingsMenuComponent; SettingsMenu {} }

    Behavior on x {
        NumberAnimation { duration: 300; easing.type: Easing.InOutQuad }
    }

    function showMenu() {
        switchTo("main")
        opened = true
        x = parent.width - width
    }

    function hideMenu() {
        x = parent.width
        opened = false
        menuIcon.state = "menu"
    }

    function switchTo(menuId) {
        if (!menuRegistry[menuId]) {
            console.warn("Unknown menu ID:", menuId)
            return
        }

        let entry = menuRegistry[menuId]
        menuHeader.headerTitle = entry.header
        menuLoader.sourceComponent = entry.component
        menuIcon.state = entry.icon
    }
}
