import QtQuick 2.15

Column {
    anchors.fill: parent

    MenuNumberInput {
        id: inputControl
        buttontext: "Polling Interval [Ms]"
        value: settingsManager.cycleIntervalMs
        minValue: 50
        maxValue: 1000

        onMinusClicked: {
            settingsManager.cycleIntervalMs -= 10
        }

        onPlusClicked: {
            settingsManager.cycleIntervalMs += 10
        }
    }

    MenuEntry {
        buttontext: "Vehicle Speed"
        hasCheckbox: true
    }

    MenuEntry {
        buttontext: "Engine Speed"
        hasCheckbox: true
    }
}
