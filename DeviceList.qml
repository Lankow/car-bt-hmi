import QtQuick 2.15
import QtQuick.Controls 2.15

Frame {
    ListView {
        implicitWidth: 250
        implicitHeight: 250

        model: deviceModel

        delegate: Row {
            width: parent.width
            height: 50

            Rectangle{
                width: parent.width
                height: parent.height

                Text{
                    anchors.centerIn: parent
                    text: model.name
                }

                MouseArea{
                    anchors.fill: parent
                    onClicked: bluetoothManager.connectToOBD(model.address)
                }
            }
        }
    }
}
