import QtQuick 2.15

Column {
    anchors.fill: parent
    signal menuSwitchRequested(string menuId)

    MenuItem{
        buttontext: "Device"
        onClicked: menuSwitchRequested("device")
    }

    MenuItem{
        // TODO: Add Menu CheckBox Component
        // TODO: Add "Save Settings" button
        // TODO: Reset Device
        buttontext: "Settings"
        onClicked: menuSwitchRequested("settings")
    }

    MenuItem{
        id: helpButton
        buttontext: "Help"
    }
}

