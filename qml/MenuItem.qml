import QtQuick 2.15

Rectangle {
    id: menuItemRoot
    height: 50
    width: parent.width
    color: menuButtonMouseArea.pressed ? "#606162" : "#404142"

    property string buttontext: ""
    property bool hasCheckbox: false
    property bool checked: false
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
        color: checked ? "#00cc66" : "#666666"
        anchors {
            right: parent.right
            verticalCenter: parent.verticalCenter
            rightMargin: 10
        }
    }

    MouseArea {
        id: menuButtonMouseArea
        anchors.fill: parent
        onClicked: {
            if (hasCheckbox){
                checked = !checked
            }else{
                menuItemRoot.clicked()
            }
        }
    }
}
