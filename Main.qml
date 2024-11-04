import QtQuick
import QtQuick.Window
import QtQuick.Controls

Window {
    flags: Qt.FramelessWindowHint

    property int displayWidth: 800
    property int displayHeight: 480

    width: displayWidth
    height: displayHeight

    minimumWidth: displayWidth
    minimumHeight: displayHeight

    maximumWidth: displayWidth
    maximumHeight: displayHeight

    visible: true
    title: qsTr("Hyundai-BT-HMI")

    Rectangle{
        id: background
        anchors.fill: parent
    }

    // 1:3 Element
        //Gauge
    // 1:3 Element
        // Other
    // 1:3 Element
        //Gauge
}
