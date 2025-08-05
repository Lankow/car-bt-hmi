import QtQuick

Rectangle {
    id: menuItemRoot
    height: 50
    width: parent.width
    color: clickable && menuButtonMouseArea.pressed ? "#606162" : "#404142"

    property string buttontext: ""
    property bool hasCheckbox: false
    property bool checked: false
    property bool clickable: true

    signal clicked()

    Rectangle {
        width: parent.width
        height: 2
        color: "#323334"
        anchors.top: parent.top
    }

    Text {
        text: buttontext
        font.family: orbitronFont.name
        font.pointSize: 14
        color: "#cfcccc"
        anchors {
            left: parent.left
            verticalCenter: parent.verticalCenter
            leftMargin: 10
        }
    }

    Rectangle {
        visible: hasCheckbox
        width: 25
        height: 25
        radius: 3
        color: checked ? "#cfcccc" : "#292828"
        anchors {
            right: parent.right
            verticalCenter: parent.verticalCenter
            rightMargin: 10
        }
    }

    MouseArea {
        id: menuButtonMouseArea
        anchors.fill: parent
        onClicked: menuItemRoot.clicked()
    }
}
