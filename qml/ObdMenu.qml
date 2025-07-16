import QtQuick 2.15

Column {
    anchors.fill: parent

    MenuNumberInput {
        id: inputControl
        buttontext: "Polling Interval"
        value: 5

        onMinusClicked: console.log("Minus clicked.")
        onPlusClicked: console.log("Plus clicked.")
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
