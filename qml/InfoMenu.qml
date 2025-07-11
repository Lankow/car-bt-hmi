import QtQuick 2.15

Column {
    anchors.fill: parent

    MenuEntry {
        buttontext: "Version: " + appVersion
        clickable: false
    }

    MenuEntry {
        id: settingsDevice
        buttontext: "Paired Device: " + (settingsManager.lastDeviceName !== "" ? "\n" + settingsManager.lastDeviceName : "None")
        clickable: false
    }

    MenuEntry {
        id: settingsAddress
        buttontext: "Address: " + (settingsManager.lastDeviceAddress !== "" ? "\n" + settingsManager.lastDeviceAddress : "None")
        clickable: false
    }
}
