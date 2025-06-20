import QtQuick 2.15
import CustomControls 1.0

Rectangle{
    color: "transparent"
    width: parent.width
    height: 50

    StateIndicator{
        size: 30
        connectionState: bluetoothManager.connectionState

        x: 10
        y: 12
    }
}
