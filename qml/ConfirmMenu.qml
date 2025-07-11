import QtQuick 2.15
import QtQuick.Controls 2.15

Column {
    id: confirmMenu
    width: parent.width
    spacing: 10
    padding: 10

    property string confirmText: ""
    property var confirmAction: null
    property var cancelAction: null

    Text {
        text: confirmText
        font.pixelSize: 16
        font.family: "Orbitron"
        color: "#cfcccc"
        wrapMode: Text.WordWrap
        width: parent.width - 20
    }

    MenuEntry {
        buttontext: "Confirm"
        onClicked: {
            if (confirmAction) {
                confirmAction()
            }
        }
    }

    MenuEntry {
        buttontext: "Cancel"
        onClicked: {
            if (cancelAction) {
                cancelAction()
            }
        }
    }
}
