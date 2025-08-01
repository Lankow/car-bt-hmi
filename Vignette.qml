import QtQuick

Canvas {
    id: vignetteCanvas
    anchors.fill: parent
    opacity: 0.7

    onPaint: {
        var ctx = getContext("2d");
        var gradient = ctx.createRadialGradient(width / 2, height / 2, 0, width / 2, height / 2, Math.max(width, height) / 2);

        gradient.addColorStop(0.7, "transparent");
        gradient.addColorStop(1.0, "black");

        ctx.fillStyle = gradient;
        ctx.fillRect(0, 0, width, height);
    }

    onWidthChanged: requestPaint()
    onHeightChanged: requestPaint()
    Component.onCompleted: requestPaint()
}
