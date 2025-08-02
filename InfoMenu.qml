import QtQuick 2.15

Column {
    anchors.fill: parent

    MenuTextBlock {
        text: "Version: " + appVersion
    }

    MenuTextBlock {
        text: "Paired Device: " + (settingsManager.lastDeviceName !== "" ? "\n" + settingsManager.lastDeviceName : "None")
    }

    MenuTextBlock {
        text: "Address: " + (settingsManager.lastDeviceAddress !== "" ? "\n" + settingsManager.lastDeviceAddress : "None")
    }
}
