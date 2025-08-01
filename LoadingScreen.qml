import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: loadingScreenRoot
    anchors.fill: parent
    z: 999
    color: "transparent"
    visible: true
    opacity: 1.0

    Image {
        source: "resources/logo.svg"
        width: 300
        fillMode: Image.PreserveAspectFit
        anchors{
            verticalCenter: parent.verticalCenter
            horizontalCenter: parent.horizontalCenter
        }
    }
}
