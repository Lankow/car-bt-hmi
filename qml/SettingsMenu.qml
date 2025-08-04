import QtQuick
import Settings 1.0

Column {
    anchors.fill: parent

    MenuEntry {
        buttontext: "Logging Enabled"
        hasCheckbox: true
        checked: settingsManager.loggingEnabled
        onClicked: settingsManager.toggleSetting(SettingsManager.LoggingEnabled)
    }

    MenuEntry {
        buttontext: "Clock Enabled"
        hasCheckbox: true
        checked: settingsManager.clockEnabled
        onClicked: settingsManager.toggleSetting(SettingsManager.ClockEnabled)
    }

    MenuEntry {
        id: resetSettingsButton
        buttontext: "Factory Reset"
        onClicked: {
            let capturedSettingsManager = settingsManager

            MenuState.showConfirm(
                "Shall Factory reset be performed? All settings will be restored to Default.",
                function () {
                    capturedSettingsManager.resetSettings();
                    MenuState.switchTo("main")
                },
                function () {
                    MenuState.goBack()
                }
            )
        }
    }
}
