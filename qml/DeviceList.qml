import QtQuick 2.15
import QtQuick.Controls 2.15

Frame {
    id: deviceListFrame
    property var bluetoothManager
    padding: 0
    width: 200
    height: 380


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
                    let bt = bluetoothManager  // capture scope-safe reference
                    let dev = model.device     // capture device
                    let deviceName = (!model.name || model.name.toLowerCase().includes(model.address.toLowerCase()))
                                    ? "Unknown device" : model.name

                    let confirmText = "Connect to device " + deviceName + "?"

                    let confirmAction = function() {
                        bt.connectToOBD(dev)
                    }

                    let cancelAction = function() {
                        menu.goBack()
                    }

                    menu.showConfirm(confirmText, confirmAction, cancelAction)
                }
            }
        }
    }
}
