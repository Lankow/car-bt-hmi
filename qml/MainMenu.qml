import QtQuick 2.15

Column {
    anchors.fill: parent
    signal menuSwitchRequested(string menuId)

    MenuButton{
        buttontext: "Device"
        onClicked: menuSwitchRequested("device")
    }

    MenuButton{
        // TODO: Add Menu CheckBox Component
        // TODO: Add "Save Settings" button
        // TODO: Reset Device
        buttontext: "Settings"
        onClicked: menuSwitchRequested("settings")
    }

    MenuButton{
        id: helpButton
        buttontext: "Help"
    }
}

