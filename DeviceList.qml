import QtQuick 2.15
import QtQuick.Controls 2.15

Frame {
    ListView {
        implicitWidth: 250
        implicitHeight: 250

        model: deviceModel

        delegate: Row {
            Button{
                text: model.address
                onClicked: bluetoothManager.startDiscovery()
            }
        }
    }
}
