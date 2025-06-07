import QtQuick 2.15

Item {
    id: root
    property int size: 10
    property int animationDuration: 350
    property color barColor: "#FFFFFF"

    width: size
    height: size

    Rectangle {
        id: bar1
        width: size
        height: size / 5
        color: barColor
    }

    Rectangle {
        id: bar2
        y: size * 2 / 5
        width: size
        height: size / 5
        color: barColor
    }

    Rectangle {
        id: bar3
        y: size * 4 / 5
        width: size
        height: size / 5
        color: barColor
    }

    state: "menu"

    states: [
        State {
            name: "menu"
        },
        State {
            name: "back"
            PropertyChanges {
                target: bar1
                rotation: -45
                width: size * 2 / 3
                y: size / 3
            }
            PropertyChanges {
                target: bar2
                width: size / 2
                x: size * 0.2
                y: size / 2
            }
            PropertyChanges {
                target: bar3
                rotation: 45
                width: size * 2 / 3
                y: size * 2 / 3
            }
        }
    ]

    transitions: [
        Transition {
            to: "*"
            PropertyAnimation {
                targets: [bar1, bar2, bar3]
                properties: "rotation, width, x, y, height"
                duration: animationDuration
                easing.type: Easing.InOutQuad
            }
        }
    ]
}
