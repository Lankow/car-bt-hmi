import QtQuick 2.15

Column {
    anchors.fill: parent

    MenuItem {
        buttontext: "Logging Enabled"
        hasCheckbox: true
        checked: settingsManager.loggingEnabled
        onClicked: settingsManager.toggleSetting(settingsManager.LoggingEnabled)
    }

    MenuItem{
        id: resetSettingsButton
        buttontext: "Factory Reset"
        onClicked: settingsManager.resetSettings();
    }
}
