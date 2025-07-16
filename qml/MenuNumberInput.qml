import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: menuNumberInputRoot
    height: 75
    width: parent.width
    color: "#404142"

    property string buttontext: ""
    property int value: 0

    signal minusClicked()
    signal plusClicked()

    Rectangle {
        width: parent.width
        height: 2
        color: "#323334"
        anchors.top: parent.top
    }

    Text {
        text: buttontext
        font.family: "Orbitron"
        font.pointSize: 14
        color: "#cfcccc"
        anchors {
            left: parent.left
            topMargin: 10
            leftMargin: 10
        }
    }

    Row {
        spacing: 20
        anchors.centerIn: parent

        Rectangle {
            width: 40
            height: 40
            color: "#2e2f30"
            radius: 5
            border.color: "#606162"

            Text {
                anchors.centerIn: parent
                text: "-"
                font.pointSize: 20
                color: "#ffffff"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    value = Math.max(0, value - 1);
                    minusClicked()
                }
            }
        }

        Text {
            id: valueText
            text: value.toString()
            font.pointSize: 18
            color: "#ffffff"
            font.family: "Orbitron"
        }

        Rectangle {
            width: 40
            height: 40
            color: "#2e2f30"
            radius: 5
            border.color: "#606162"

            Text {
                anchors.centerIn: parent
                text: "+"
                font.pointSize: 20
                color: "#ffffff"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    value = value + 1;
                    plusClicked()
                }
            }
        }
    }
}
