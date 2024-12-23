#include "gauge.h"
#include <QPainter>

Gauge::Gauge(QQuickItem *parent)
    :QQuickPaintedItem(parent),
    m_gaugeValue(50),
    m_gaugeSize(500),
    m_startAngle(50),
    m_alignAngle(260), // 360 - 2 * m_startAngle
    m_lowestRange(0),
    m_highestRange(200),
    m_arcWidth(20),
    m_outerColor(QColor(100, 100, 100)),
    m_innerColor(QColor(41, 40, 40)),
    m_textColor(QColor(207, 204, 204)),
    m_backgroundColor(QColor(Qt::transparent))
{
}

void Gauge::paint(QPainter *painter)
{
    QRectF rect = this->boundingRect();
    painter->setRenderHint(QPainter::Antialiasing);
    QPen pen = painter->pen();
    pen.setCapStyle(Qt::RoundCap);

    // Inner Part
    double startAngle;
    double spanAngle;

    startAngle = m_startAngle - 190;
    spanAngle = 0 - m_alignAngle;

    painter->save();
    pen.setWidth(m_arcWidth);
    pen.setColor(m_innerColor);

    painter->setPen(pen);
    painter->drawArc(rect.adjusted(m_arcWidth, m_arcWidth, -m_arcWidth, -m_arcWidth), startAngle * 16, spanAngle * 16);
    painter->restore();

    // Text
    painter->save();
    QFont font("Halvetica", 70, QFont::Bold);
    painter->setFont(font);
    pen.setColor(m_textColor);
    painter->setPen(pen);
    painter->drawText(rect.adjusted(m_gaugeSize/30, m_gaugeSize/30, -m_gaugeSize/30, -m_gaugeSize/5), Qt::AlignCenter, QString::number(m_gaugeValue));
    painter->restore();

    // Outer Part
    painter->save();
    pen.setWidth(m_arcWidth);
    pen.setColor(m_outerColor);
    qreal valueToAngle = ((m_gaugeValue - m_lowestRange)/(m_highestRange - m_lowestRange)) * spanAngle;
    painter->setPen(pen);
    painter->drawArc(rect.adjusted(m_arcWidth, m_arcWidth, -m_arcWidth, -m_arcWidth), startAngle * 16, valueToAngle * 16);
    painter->restore();
}

//Setters
void Gauge::setGaugeValue(qreal gaugeValue)
{
    if(m_gaugeValue == gaugeValue) return;

    m_gaugeValue = gaugeValue;
    update(); // Drawer update when value represented on gauge has changed
    emit gaugeValueChanged(); // signal to QML side
}

void Gauge::setGaugeSize(qreal size)
{
    if(m_gaugeSize == size) return;

    m_gaugeSize = size;
    emit gaugeSizeChanged(); // signal to QML side
}

void Gauge::setStartAngle(qreal startAngle)
{
    if(m_startAngle == startAngle) return;

    m_startAngle = startAngle;
    emit startAngleChanged(); // signal to QML side
}

void Gauge::setAlignAngle(qreal alignAngle)
{
    if(m_alignAngle == alignAngle) return;

    m_alignAngle = alignAngle;
    emit alignAngleChanged(); // signal to QML side
}

void Gauge::setLowestRange(qreal lowestRange)
{
    if(m_lowestRange == lowestRange) return;

    m_lowestRange = lowestRange;
    emit lowestRangeChanged(); // signal to QML side
}

void Gauge::setHighestRange(qreal highestRange)
{
    if(m_highestRange == highestRange) return;

    m_highestRange = highestRange;
    emit highestRangeChanged(); // signal to QML side
}

void Gauge::setArcWidth(int arcWidth)
{
    if(m_arcWidth == arcWidth) return;

    m_arcWidth = arcWidth;
    emit arcWidthChanged(); // signal to QML side
}

void Gauge::setOuterColor(QColor outerColor)
{
    if(m_outerColor == outerColor) return;

    m_outerColor = outerColor;
    emit outerColorChanged(); // signal to QML side
}

void Gauge::setInnerColor(QColor innerColor)
{
    if(m_innerColor == innerColor) return;

    m_innerColor = innerColor;
    emit innerColorChanged(); // signal to QML side
}

void Gauge::setTextColor(QColor textColor)
{
    if(m_textColor == textColor) return;

    m_textColor = textColor;
    emit textColorChanged(); // signal to QML side
}

void Gauge::setBackgroundColor(QColor backgroundColor)
{
    if(m_backgroundColor == backgroundColor) return;

    m_backgroundColor = backgroundColor;
    emit backgroundColorChanged(); // signal to QML side
}

// Getters
qreal Gauge::getGaugeValue()
{
    return m_gaugeValue;
}

qreal Gauge::getGaugeSize()
{
    return m_gaugeSize;
}
qreal Gauge::getStartAngle()
{
    return m_startAngle;
}

qreal Gauge::getAlignAngle()
{
    return m_alignAngle;
}

qreal Gauge::getLowestRange()
{
    return m_lowestRange;
}

qreal Gauge::getHighestRange()
{
    return m_highestRange;
}

int Gauge::getArcWidth()
{
    return m_arcWidth;
}

QColor Gauge::getOuterColor()
{
    return m_outerColor;
}

QColor Gauge::getInnerColor()
{
    return m_innerColor;
}

QColor Gauge::getTextColor()
{
    return m_textColor;
}

QColor Gauge::getBackgroundColor()
{
    return m_backgroundColor;
}


