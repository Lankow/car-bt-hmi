import QtQuick 2.15

Column {
    anchors.fill: parent

    MenuEntry {
        buttontext: "Logging Enabled"
        hasCheckbox: true
        checked: settingsManager.loggingEnabled
        onClicked: settingsManager.toggleSetting(settingsManager.LoggingEnabled)
    }

    MenuEntry{
        id: resetSettingsButton
        buttontext: "Factory Reset"
        onClicked: settingsManager.resetSettings();
    }
}
