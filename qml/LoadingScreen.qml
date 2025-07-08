import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: loadingScreenRoot
    anchors.fill: parent
    z: 999
    color: "transparent"
    visible: true
    opacity: 1.0

    Image {
        source: "../resources/logo.svg"
        width: 300
        fillMode: Image.PreserveAspectFit
        anchors{
            verticalCenter: parent.verticalCenter
            horizontalCenter: parent.horizontalCenter
        }
    }
}
