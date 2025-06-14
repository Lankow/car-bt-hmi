import QtQuick 2.15
import QtQuick.Controls 2.15

Frame {
    id: deviceListFrame
    padding: 0
    width: 200
    height: 420

    background: Rectangle {
        color: "#1e1e1e"
        border.color: "#323334"
        border.width: 1
    }

    ListView {
        id: deviceListView
        anchors.fill: parent
        anchors.margins: 4
        spacing: 4
        clip: true

        model: deviceModel

        delegate: Rectangle {
            id: itemRect
            width: parent.width
            height: 50
            color: "#2a2a2a"
            border.color: "#444"
            border.width: 1

            Text {
                anchors.centerIn: parent
                text: (!model.name || model.name.toLowerCase().includes(model.address.toLowerCase()))
                      ? "Unknown device"
                      : model.name
                color: "white"
                font.pixelSize: 16
                font.family: "Orbitron"
            }

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                onClicked: {
                    // TODO: Open "Connecting to BT Device" Screen
                    bluetoothManager.connectToOBD(model.device)
                }
            }
        }
    }
}
