import QtQuick

Column {
    anchors.fill: parent
    signal menuSwitchRequested(string menuId)

    MenuEntry{
        buttontext: "Pair Device"
        onClicked: menuSwitchRequested("device")
    }

    MenuEntry{
        buttontext: "OBD PIDs"
        onClicked: menuSwitchRequested("obd")
    }

    MenuEntry{
        buttontext: "Settings"
        onClicked: menuSwitchRequested("settings")
    }

    MenuEntry{
        buttontext: "Device Info"
        onClicked: menuSwitchRequested("info")
    }
}

