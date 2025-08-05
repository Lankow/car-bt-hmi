import QtQuick

Rectangle{
    color: "transparent"
    width: parent.width
    height: 50

    property string headerTitle: "CAR-BT-HMI"

    Text{
        text: headerTitle
        font.family: orbitronFont.name
        font.pointSize: 18

        x: 10
        y: 12
        color: "#cfcccc"
    }
}
