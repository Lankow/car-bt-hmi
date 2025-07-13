import QtQuick 2.15

Rectangle {
    id: menuTextBlockRoot
    width: parent.width
    height: 150
    color: "#292828"
    property alias text: textBlock.text

    Rectangle {
        width: parent.width
        height: 2
        color: "#323334"
        anchors.top: parent.top
    }

    Text {
        id: textBlock
        wrapMode: Text.WordWrap
        font.family: "Orbitron"
        font.pointSize: 14
        color: "#cfcccc"
        anchors {
            left: parent.left
            right: parent.right
            margins: 10
            top: parent.top
            bottom: parent.bottom
        }
    }
}
