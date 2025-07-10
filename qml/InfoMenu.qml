import QtQuick 2.15

Column {
    anchors.fill: parent

    MenuItem {
        buttontext: "Version: " + appVersion
        clickable: false
    }

    MenuItem {
        id: settingsDevice
        buttontext: "Paired Device: " + (settingsManager.lastDeviceName !== "" ? "\n" + settingsManager.lastDeviceName : "None")
        clickable: false
    }

    MenuItem {
        id: settingsAddress
        buttontext: "Address: " + (settingsManager.lastDeviceAddress !== "" ? "\n" + settingsManager.lastDeviceAddress : "None")
        clickable: false
    }
}
