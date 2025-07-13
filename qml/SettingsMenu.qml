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
