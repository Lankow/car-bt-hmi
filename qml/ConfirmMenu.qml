import QtQuick 2.15
import QtQuick.Controls 2.15
import MenuState 1.0

Column {
    id: confirmMenu
    width: parent.width
    spacing: 10

    Text {
        text: MenuState.confirmText
        font.pixelSize: 16
        font.family: "Orbitron"
        color: "#cfcccc"
        wrapMode: Text.WordWrap
        width: parent.width - 20
    }

    MenuEntry {
        buttontext: "Confirm"
        onClicked: {
            if (MenuState.confirmAction) {
                MenuState.confirmAction()
            }
            MenuState.clearConfirm()
        }
    }

    MenuEntry {
        buttontext: "Cancel"
        onClicked: {
            if (MenuState.cancelAction) {
                MenuState.cancelAction()
            }
            MenuState.clearConfirm()
        }
    }
}
