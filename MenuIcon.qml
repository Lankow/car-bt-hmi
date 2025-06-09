import QtQuick 2.15

Item {
    id: root
    property int size: 10
    property int animationDuration: 350
    property color barColor: "#FFFFFF"
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
            width: root.width
            height: root.barHeight
            color: root.barColor
            y: index * root.barSpacing
        }
    }

    states: [
        State {
            name: "menu"
        },
        State {
            name: "close"
            PropertyChanges { target: root.children[0]; rotation: -45; height: root.barHeight * 0.6; width: size * 0.8; x: width / 2; y: size / 2}
            PropertyChanges { target: root.children[1]; opacity: 0 }
            PropertyChanges { target: root.children[2]; rotation: 45; height: root.barHeight * 0.6; width: size * 0.8; x: width / 2; y: size / 2}
        },
        State {
            name: "back-left"
            PropertyChanges { target: root.children[0]; rotation: -45; width: size * 2 / 3; x: size / 2; y: size / 3 }
            PropertyChanges { target: root.children[1]; opacity: 0 }
            PropertyChanges { target: root.children[2]; rotation: 45; width: size * 2 / 3; x: size / 2; y: size * 2 / 3 }
        },
        State {
            name: "back-right"
            PropertyChanges { target: root.children[0]; rotation: 45; width: size * 2 / 3; x: size / 2; y: size / 3 }
            PropertyChanges { target: root.children[1]; opacity: 0 }
            PropertyChanges { target: root.children[2]; rotation: -45; width: size * 2 / 3; x: size / 2; y: size * 2 / 3 }
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
}
