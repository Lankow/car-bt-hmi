import QtQuick
import QtQuick.Controls
import MenuState 1.0

Rectangle {
    id: deviceListBackground
    width: parent.width
    height: root.height * 0.8
    color: "transparent"

    ListView {
        id: deviceListView
        anchors.fill: parent
        clip: true
        spacing: 0

        model: deviceModel

        delegate: MenuEntry {
            width: parent.width
            buttontext: (!model.name || model.name.toLowerCase().includes(model.address.toLowerCase()))
                        ? "Unknown device"
                        : model.name

            onClicked: {
                let capturedDevice = model.device
                let capturedBtManager = bluetoothManager

                MenuState.showConfirm(
                            "Connect to " + model.name + "?",
                            function () {
                                capturedBtManager.connectToOBD(capturedDevice)
                                MenuState.switchTo("main")
                            },
                            function () {
                                MenuState.goBack()
                            }
                            )
            }
        }
    }
}
