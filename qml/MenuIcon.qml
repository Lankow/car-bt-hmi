import QtQuick 2.15
import MenuState 1.0

Item {
    id: menuIconRoot
    property int size: 10
    property int animationDuration: 350
    property color barColor: menuIconMouseArea.pressed ? "#606162" : "#cfcccc"
    property string iconState: "menu"

    width: size * 1.5
    height: size
    state: iconState

    readonly property int barHeight: size / 5
    readonly property real barSpacing: size * 2 / 5

    Repeater {
        model: 3
        Rectangle {
            id: bar
            width: menuIconRoot.width
            height: menuIconRoot.barHeight
            color: menuIconRoot.barColor
            y: index * menuIconRoot.barSpacing
            radius: size
        }
    }

    states: [
        State {
            name: "menu"
        },
        State {
            name: "close"
            PropertyChanges { target: menuIconRoot.children[0]; rotation: -45; height: menuIconRoot.barHeight * 0.6; width: size * 0.8; x: width / 2; y: size / 2}
            PropertyChanges { target: menuIconRoot.children[1]; opacity: 0 }
            PropertyChanges { target: menuIconRoot.children[2]; rotation: 45; height: menuIconRoot.barHeight * 0.6; width: size * 0.8; x: width / 2; y: size / 2}
        },
        State {
            name: "back-left"
            PropertyChanges { target: menuIconRoot.children[0]; rotation: -45; width: size * 2 / 3; x: size / 2; y: size / 3 }
            PropertyChanges { target: menuIconRoot.children[1]; opacity: 0 }
            PropertyChanges { target: menuIconRoot.children[2]; rotation: 45; width: size * 2 / 3; x: size / 2; y: size * 2 / 3 }
        },
        State {
            name: "back-right"
            PropertyChanges { target: menuIconRoot.children[0]; rotation: 45; width: size * 2 / 3; x: size / 2; y: size / 3 }
            PropertyChanges { target: menuIconRoot.children[1]; opacity: 0 }
            PropertyChanges { target: menuIconRoot.children[2]; rotation: -45; width: size * 2 / 3; x: size / 2; y: size * 2 / 3 }
        }
    ]

    transitions: [
        Transition {
            to: "*"
            PropertyAnimation {
                properties: "opacity, rotation, height, width, x, y"
                duration: animationDuration
                easing.type: Easing.InOutQuad
            }
        }
    ]

    MouseArea {
        id: menuIconMouseArea
        anchors.fill: parent
        onClicked: {
            if (MenuState.currentMenuId === "closed") {
                MenuState.switchTo("main")
            } else if (MenuState.currentMenuId === "main") {
                MenuState.switchTo("closed")
            } else {
                MenuState.goBack()
            }
        }
    }
}
