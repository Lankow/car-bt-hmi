import QtQuick
import QtQuick.Controls
import MenuState 1.0

Column {
    id: confirmMenu
    width: parent.width

    MenuTextBlock {
        text: MenuState.confirmText
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
