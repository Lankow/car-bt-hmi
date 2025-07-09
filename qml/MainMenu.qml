import QtQuick 2.15

Column {
    anchors.fill: parent
    signal menuSwitchRequested(string menuId)

    MenuItem{
        buttontext: "Device"
        onClicked: menuSwitchRequested("device")
    }

    MenuItem{
        buttontext: "Settings"
        onClicked: menuSwitchRequested("settings")
    }

    MenuItem{
        id: helpButton
        buttontext: "Help"
        onClicked: menuSwitchRequested("help")
    }
}

