import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import com.voknal.gauge 1.0

Window {
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
    title: qsTr("Hyundai-BT-HMI")
    color:"#000"

    Text{
        objectName: "clock"
        text: "--:--"
        color: "#fff"
        font.pointSize: 30
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 30
    }

    Text{
        objectName: "carMileage"
        text: "---- km"
        color: "#fff"
        font.pointSize: 30
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
    }

    Gauge{
        objectName: "speedGauge"
        gaugeValue: gaugeValue
        gaugeSize: 350
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 30
        width: gaugeSize
        height: gaugeSize
        startAngle: startAngle
        alignAngle: alignAngle
        lowestRange: lowestRange
        highestRange: highestRange
        arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
    }

    Gauge{
        objectName: "rpmGauge"
        gaugeValue: gaugeValue
        gaugeSize: 350
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 30
        width: gaugeSize
        height: gaugeSize
        startAngle: startAngle
        alignAngle: alignAngle
        lowestRange: lowestRange
        highestRange: highestRange
        arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
    }
}
