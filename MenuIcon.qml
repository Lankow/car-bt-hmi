import QtQuick 2.15


Item {
  id: root
  property int size: 10
  pro
  width: size
  height: size

  Rectangle {
    id: bar1
    width: size
    height: size/5
    antialiasing: true
  }

  Rectangle {
    id: bar2
    y: (size/5)*2
    width: size
    height: size/5
    antialiasing: true
  }

  Rectangle {
    id: bar3
    y: (size/5)*4
    width: size
    height: size/5
    antialiasing: true
  }

  property int animationDuration: 350

  state: "menu"
  states: [
    State {
      name: "menu"
    },

    State {
      name: "back"
      PropertyChanges { target: root; rotation: 180 }
      PropertyChanges { target: bar1; rotation: 45; width: 13; x: 9.5; y: 8 }
      PropertyChanges { target: bar2; width: 17; x: 3; y: 12 }
      PropertyChanges { target: bar3; rotation: -45; width: 13; x: 9.5; y: 16 }
    }
  ]

  transitions: [
    Transition {
      RotationAnimation { target: root; direction: RotationAnimation.Clockwise; duration: animationDuration; easing.type: Easing.InOutQuad }
      PropertyAnimation { target: bar1; properties: "rotation, width, x, y"; duration: animationDuration; easing.type: Easing.InOutQuad }
      PropertyAnimation { target: bar2; properties: "rotation, width, x, y"; duration: animationDuration; easing.type: Easing.InOutQuad }
      PropertyAnimation { target: bar3; properties: "rotation, width, x, y"; duration: animationDuration; easing.type: Easing.InOutQuad }
    }
  ]
}
