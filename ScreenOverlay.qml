import QtQuick
import MenuState 1.0

Rectangle {
    id: overlay
    anchors.fill: parent
    opacity: MenuState.currentMenuId === "closed" ? 0.0 : 0.4
    color: "#000"
    z: 99
    visible: MenuState.currentMenuId !== "closed"

    MouseArea {
        anchors {
            top: parent.top
            left: parent.left
            bottom: parent.bottom
        }
        width: parent.width - 250
        onClicked: MenuState.switchTo("closed")
    }

    Behavior on opacity {
        NumberAnimation { duration: 300 }
    }
}
