#include "gauge.h"
#include <QPainter>

Gauge::Gauge(QQuickItem *parent)
    :QQuickPaintedItem(parent),
    m_gaugeValue(2000),
    m_gaugeSize(500),
    m_startAngle(50),
    m_alignAngle(260), // 360 - 2 * m_startAngle
    m_lowestRange(0),
    m_highestRange(200),
    m_arcWidth(10),
    m_outerColor(QColor(10,15,245)),
    m_innerColor(QColor(50,85,255)),
    m_textColor(QColor(255,255,255)),
    m_backgroundColor(QColor(Qt::transparent))
{

}

void Gauge::paint(QPainter *painter)
{
    QRectF rect = this->boundingRect();
    painter->setRenderHint(QPainter::Antialiasing);
    QPen pen = painter->pen();
    pen.setCapStyle(Qt::FlatCap);

    double startAngle;
    double spanAngle;

    startAngle = m_startAngle;
    spanAngle = 0 - m_alignAngle;
}

void Gauge::setGaugeSize(qreal size)
{
    if(m_gaugeSize == size) return;

    m_gaugeSize = size;
    emit gaugeSizeChanged(); // signal to QML side
}

qreal Gauge::getGaugeSize()
{
    return m_gaugeSize;
}


