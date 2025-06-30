import QtQuick 2.15

Rectangle {
    id: overlay
    anchors.fill: parent
    opacity: sideMenu.opened ? 0.4 : 0.0
    color: "#000"
    z: 99

    MouseArea {
        anchors{
            top: parent.top
            left: parent.left
            bottom: parent.bottom
        }
        width: parent.width - sideMenu.width
        onClicked: sideMenu.opened ? sideMenu.hideMenu() : ""
    }

    Behavior on opacity { NumberAnimation { duration: 300 } }
}
