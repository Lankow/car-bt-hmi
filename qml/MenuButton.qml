import QtQuick 2.15

Rectangle {
    id: menuButtonRoot
    height: 50
    width: parent.width
    color: menuButtonMouseArea.pressed ? "#606162" : "#404142"

    property string buttontext: ""
    signal clicked()

    Rectangle {
        width: parent.width
        height: 2
        color: "#323334"
    }

    Text {
        text: buttontext
        font.family: "Orbitron"
        font.pointSize: 14
        anchors.leftMargin: 10
        color: "#cfcccc"
        anchors {
            left: parent.left
            verticalCenter: parent.verticalCenter
            leftMargin: 10
        }
    }

    MouseArea {
        id: menuButtonMouseArea
        anchors.fill: parent
        onClicked: menuButtonRoot.clicked()
    }
}
