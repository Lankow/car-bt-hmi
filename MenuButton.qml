import QtQuick 2.15

Rectangle{
    height:50
    width: parent.width
    color: "#404142"

    property string buttontext: ""

    Rectangle{
        width: parent.width
        height: 2
        color: "#323334"
    }

    Text{
        text: buttontext
        font.family: "Orbitron"
        font.pointSize: 14
        anchors.leftMargin: 10
        color: "#cfcccc"
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
    }
}
