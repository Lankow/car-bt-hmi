import QtQuick 2.15
import QtQuick.Controls 2.15
import MenuState 1.0

Rectangle {
    id: menu
    width: 250
    height: parent.height
    color: "#292828"
    z: 999

    MenuHeader {
        id: menuHeader
        anchors.top: parent.top
        anchors.left: parent.left
    }

    Loader {
        id: menuLoader
        width: parent.width
        anchors.top: menuHeader.bottom
        sourceComponent: MenuState.menuRegistry[MenuState.currentMenuId]?.component

        onLoaded: {
            if (item && item.menuSwitchRequested) {
                item.menuSwitchRequested.connect(MenuState.switchTo)
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
    Component { id: obdMenuComponent; ObdMenu {} }
    Component { id: settingsMenuComponent; SettingsMenu {} }
    Component { id: infoMenuComponent; InfoMenu {} }
    Component { id: confirmMenuComponent; ConfirmMenu {} }

    Behavior on x {
        NumberAnimation { duration: 300; easing.type: Easing.InOutQuad }
    }

    Connections {
        target: MenuState
        onMenuChanged: {
            let entry = MenuState.menuRegistry[MenuState.currentMenuId]
            if (entry) {
                menuHeader.headerTitle = entry.header
                menuLoader.sourceComponent = entry.component
                menuIcon.state = entry.icon
                menu.x = (MenuState.currentMenuId === "closed") ? parent.width : parent.width - menu.width
            } else {
                console.warn("Unknown menu ID:", MenuState.currentMenuId)
            }
        }
    }

    Component.onCompleted: {
        MenuState.registerComponent("main", mainMenuComponent)
        MenuState.registerComponent("device", deviceMenuComponent)
        MenuState.registerComponent("obd", obdMenuComponent)
        MenuState.registerComponent("settings", settingsMenuComponent)
        MenuState.registerComponent("info", infoMenuComponent)
        MenuState.registerComponent("confirm", confirmMenuComponent)

        MenuState.menuChanged()
    }
}
