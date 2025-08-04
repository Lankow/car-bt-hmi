import QtQuick

Rectangle {
    id: menuTextBlockRoot
    width: parent.width
    color: "#292828"
    property alias text: textBlock.text
    height: 2 + textBlock.implicitHeight + 20

    Rectangle {
        id: topBorder
        width: parent.width
        height: 2
        color: "#323334"
        anchors.top: parent.top
    }

    Text {
        id: textBlock
        wrapMode: Text.WordWrap
        width: parent.width - 20
        anchors.top: topBorder.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        font.family: "Orbitron"
        font.pointSize: 14
        color: "#cfcccc"
    }
}
