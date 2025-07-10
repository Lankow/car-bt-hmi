import QtQuick 2.15

Column {
    anchors.fill: parent
    signal menuSwitchRequested(string menuId)

    MenuItem{
        buttontext: "Device"
        onClicked: menuSwitchRequested("device")
    }

    MenuItem{
        buttontext: "OBD PIDs"
        onClicked: menuSwitchRequested("obd")
    }

    MenuItem{
        buttontext: "Settings"
        onClicked: menuSwitchRequested("settings")
    }

    MenuItem{
        buttontext: "Device Info"
        onClicked: menuSwitchRequested("info")
    }
}

