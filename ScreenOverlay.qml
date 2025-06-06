import QtQuick 2.15

Rectangle {
    id: overlay
    anchors.fill: parent
    visible: sideMenu.visible
    color: "#80000000"
    z: 99

    MouseArea {
        anchors.fill: parent
        onClicked: {
            sideMenu.hideMenu()
        }
    }
}
