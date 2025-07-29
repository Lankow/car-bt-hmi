import QtQuick 2.15
import QtQuick.Controls 2.15
import QtCore
import CustomControls 1.0

ApplicationWindow {
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

        ScreenOverlay {}

        MenuIcon {
            id: menuIcon
            size: 30
            state: "menu"
            z: 101
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.margins: 10
        }

        Gauge {
            enabled: settingsManager.vehicleSpeedEnabled
            value: settingsManager.vehicleSpeedEnabled ? dataProvider.vehicleSpeed : 0
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

        Gauge {
            enabled: settingsManager.engineSpeedEnabled
            value: settingsManager.engineSpeedEnabled ? dataProvider.engineSpeed : 0
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
            anchors{
                top: parent.top
                bottom: parent.bottom
            }
            height: parent.height
            width: 250
            x: parent.width
            z: 100
        }

        Clock {
            id: clock
            visible: settingsManager.clockEnabled
            anchors {
                bottom: parent.bottom
                horizontalCenter: parent.horizontalCenter
            }
        }
    }

    ScreenTransition {
        id: screenTransition
        loadingScreen: loadingScreen
        mainContent: mainContent
        onOnFinished: loadingScreen.visible = false
        running: true
    }
}
