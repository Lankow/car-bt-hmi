import QtQuick 2.15

Column {
    anchors.fill: parent

    MenuButton{
        id: clearSettingsButton
        buttontext: "Clear Settings"
        onClicked: settingsManager.clearSettings();
    }

    MenuButton{
        id: settingsDevice
        buttontext: "Device: " + appSettings.value("lastDeviceName", "None")
    }
}
