import QtQuick 2.15

Column {
    anchors.fill: parent

    MenuItem{
        id: clearSettingsButton
        buttontext: "Clear Settings"
        onClicked: settingsManager.clearSettings();
    }

    MenuItem {
        buttontext: "Logging Enabled"
        hasCheckbox: true
        checked: settingsManager.loggingEnabled
        onClicked: settingsManager.toggleSetting(settingsManager.LoggingEnabled)
    }

    MenuItem{
        id: settingsDevice
        buttontext: "Device: " + appSettings.value("lastDeviceName", "None")
    }
}
