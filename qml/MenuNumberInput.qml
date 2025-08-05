import QtQuick
import QtQuick.Controls

Rectangle {
    id: menuNumberInputRoot
    height: 90
    width: parent.width
    color: "#404142"

    property string buttontext: ""

    property int value: 0
    property int minValue: 0
    property int maxValue: 100000

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
        font.family: orbitronFont.name
        font.pointSize: 16
        color: "#cfcccc"
        anchors {
            left: parent.left
            top: parent.top
            topMargin: 10
            leftMargin: 10
        }
    }

    Rectangle{
        width: parent.width
        height: (parent.height / 3 ) * 2
        color: "transparent"
        anchors.bottom: parent.bottom

        Rectangle {
            width: 40
            height: 40
            color: value > minValue ? "#2e2f30" : "#5a5b5c"
            radius: 5
            border.color: "#606162"

            anchors{
                left: parent.left
                verticalCenter: parent.verticalCenter
                leftMargin: 10
            }

            Text {
                anchors.centerIn: parent
                text: "-"
                font.pointSize: 20
                color: value > minValue ? "#ffffff" : "#a0a0a0"
                font.family: orbitronFont.name
            }

            MouseArea {
                anchors.fill: parent
                enabled: value>minValue
                onClicked: minusClicked()
            }
        }

        Text {
            id: valueText
            text: value.toString()
            font.pointSize: 18
            color: "#ffffff"
            font.family: orbitronFont.name


            anchors{
                verticalCenter: parent.verticalCenter
                horizontalCenter: parent.horizontalCenter
            }
        }

        Rectangle {
            width: 40
            height: 40
            color: value < maxValue ? "#2e2f30" : "#5a5b5c"
            radius: 5
            border.color: "#606162"

            anchors{
                right: parent.right
                verticalCenter: parent.verticalCenter
                rightMargin: 10
            }

            Text {
                anchors.centerIn: parent
                text: "+"
                font.pointSize: 20
                color: value < maxValue ? "#ffffff" : "#a0a0a0"
                font.family: orbitronFont.name
            }

            MouseArea {
                anchors.fill: parent
                enabled: value<maxValue
                onClicked: plusClicked()
            }
        }
    }
}
