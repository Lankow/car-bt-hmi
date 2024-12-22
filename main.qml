import QtQuick 2.15
import QtQuick.Controls 2.15
import com.voknal.gauge 1.0

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

    Gauge{
        Text{text: qsTr("Gauge")}
    }
}
