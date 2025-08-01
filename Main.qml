import QtQuick

Window {
    id: root
    width: 800
    height: 480
    visible: true
    color: "#141414"
    title: qsTr("CAR-BT-HMI")

    Vignette {}

    LoadingScreen {
        id: loadingScreen
        anchors.fill: parent
        z: 999
        opacity: 1.0
    }

    Item {
        id: mainContent
        anchors.fill: parent
        opacity: 0.0
        scale: 0.96
        z: 1
    }
}
