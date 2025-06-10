import QtQuick 2.15
import QtQuick.Controls 2.15
import com.voknal.gauge 1.0

ApplicationWindow {

    // Uncomment below to keep frame borderless.
    // flags: Qt.FramelessWindowHint

    property int displayWidth: 800
    property int displayHeight: 480

    width: displayWidth
    height: displayHeight

    minimumWidth: displayWidth
    minimumHeight: displayHeight

    maximumWidth: displayWidth
    maximumHeight: displayHeight

    visible: true
    title: qsTr("CAR-BT-HMI")
    color:"#141414"

    Vignette {}
    LoadingScreen{}
    ScreenOverlay{}

    MenuIcon {
        id: menuIcon
        size: 30
        state: "menu"
        barColor: "#cfcccc"
        z: 101

        anchors.top: parent.top
        anchors.right: parent.right
        anchors.topMargin: 10
        anchors.rightMargin: 10

        MouseArea {
            anchors.fill: parent
            onClicked: menuIcon.state === "close" ? sideMenu.hideMenu() : sideMenu.showMenu()
        }
    }

    Gauge{
        value: dataProvider.vehicleSpeed
        unit: "Km/h"
        size: 350
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 30
        width: size
        height: size
        minValue: 0
        maxValue: 200
    }

    Gauge{
        value: dataProvider.engineSpeed
        unit: "RPM"
        size: 350
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 30
        width: size
        height: size
        minValue: 0
        maxValue: 5000
    }

    SideMenu {
        id: sideMenu
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        height: parent.height
        width: 250
        x: parent.width
        z: 100
    }
}
