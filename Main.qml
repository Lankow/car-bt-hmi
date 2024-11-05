import QtQuick
import QtQuick.Window
import QtQuick.Controls

Window {
    // flags: Qt.FramelessWindowHint

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

        Row {
            anchors.centerIn: parent
            spacing: 10

            Gauge {
                size: 160
                colorCircle: "#0092CC"
                colorBackground: "#E6E6E6"
                arcBegin: 0
                arcEnd: 270
                lineWidth: 10
            }

            Gauge {
                size: 160
                colorCircle: "#FF3333"
                colorBackground: "#E6E6E6"
                 showBackground: true
                 arcBegin: 0
                 arcEnd: 220
            }
            Gauge {
                size: 160
                colorCircle: "#779933"
                colorBackground: "#E6E6E6"
                 showBackground: true
                isPie: true
                arcBegin: 90
                arcEnd: 200
            }
            Text {
                text: "HMI Menu"
                font.family: "Helvetica"
                font.pointSize: 24
                color: "red"
            }
        }
    }

}
