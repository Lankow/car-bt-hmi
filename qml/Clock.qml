import QtQuick
import QtQuick.Controls

Rectangle {
    id: clockRoot
    width: 200
    height: 80
    color: "transparent"

    Timer {
        id: timer
        interval: 1000
        running: true
        repeat: true
        onTriggered: {
            const now = new Date()
            let h = now.getHours().toString().padStart(2, '0')
            let m = now.getMinutes().toString().padStart(2, '0')
            hoursText.text = h
            minutesText.text = m
            colon.opacity = colon.opacity === 1 ? 0 : 1
        }
    }

    Row {
        anchors.centerIn: parent
        spacing: 0

        Text {
            id: hoursText
            font.family: "Orbitron"
            font.pointSize: 28
            color: "#cfcccc"
            text: "00"
        }

        Text {
            id: colon
            text: ":"
            font.family: "Orbitron"
            font.pointSize: 28
            color: "#cfcccc"
            opacity: 1
        }

        Text {
            id: minutesText
            font.family: "Orbitron"
            font.pointSize: 28
            color: "#cfcccc"
            text: "00"
        }
    }
}
