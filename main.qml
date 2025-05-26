import QtQuick
import QtQuick.Controls
import com.app.bluetooth 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("CAR-BT-HMI")

    BluetoothManager {
        id: btManager
    }

    Column {
        anchors.centerIn: parent
        spacing: 10
        Button {
            text: "Start Scan for OBD Device."
            onClicked: btManager.startDiscovery()
        }

        Button {
            text: "Stop Scan for OBD Device."
            onClicked: btManager.stopDiscovery()
        }

        Button {
            text: "Connect to OBD Device."
            onClicked: btManager.connectToOBD()
        }
    }
}
