import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: menu
    width: 250
    height: parent.height
    color: "#292828"
    z: 999

    property string currentMenuId: "closed"
    property var menuHistory: []

    property var menuRegistry: ({
        closed: {
            id: "closed",
            header: "",
            icon: "menu",
            component: null
        },
        main: {
            id: "main",
            header: "CAR-BT-HMI",
            icon: "close",
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
        },
        help: {
            id: "help",
            header: "Help",
            icon: "back-left",
            component: helpMenuComponent
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
    Component { id: helpMenuComponent; HelpMenu {} }

    Behavior on x {
        NumberAnimation { duration: 300; easing.type: Easing.InOutQuad }
    }

    function goBack() {
        if (menuHistory.length > 0) {
            let previousId = menuHistory.pop()
            switchTo(previousId)
        } else {
            switchTo("main")
        }
    }

    function switchTo(menuId) {
        if (!menuRegistry[menuId]) {
            console.warn("Unknown menu ID:", menuId)
            return
        }

        if (menuId === "closed") {
            menuHistory = []
        } else if (currentMenuId !== "closed" && currentMenuId !== menuId) {
            menuHistory.push(currentMenuId)
        }
        currentMenuId = menuId
        let entry = menuRegistry[menuId]

        x = (menuId === "closed") ? parent.width : parent.width - width
        menuHeader.headerTitle = entry.header
        menuLoader.sourceComponent = entry.component
        menuIcon.state = entry.icon
    }
}
