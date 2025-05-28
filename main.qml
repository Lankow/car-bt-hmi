import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 400
    height: 600
    title: "Bluetooth Devices"

    Button {
        text: "Start Scan for OBD Device."
        onClicked: bluetoothManager.startDiscovery()
    }


    ListView {
        anchors.fill: parent
        model: deviceModel
        spacing: 8
        delegate: Rectangle {
            width: parent.width
            height: 80
            color: "whitesmoke"
            border.color: "lightgray"
            radius: 10

            Row {
                anchors.fill: parent
                spacing: 10
                anchors.margins: 10

                Column {
                    width: parent.width * 0.7
                    anchors.verticalCenter: parent.verticalCenter

                    Text {
                        text: name
                        font.bold: true
                    }

                    Text {
                        text: address
                        font.pointSize: 10
                        color: "gray"
                    }
                }

                Button {
                    text: "Connect"
                    anchors.verticalCenter: parent.verticalCenter
                    onClicked: {
                        bluetoothManager.connectToDevice(address);
                    }
                }
            }
        }
            }

}
