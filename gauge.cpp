#include "gauge.h"
#include <QPainter>

// Constants
namespace {
constexpr qreal defaultGaugeValue = 50;
constexpr qreal defaultGaugeSize = 500;

constexpr qreal defaultLowestRange = 0;
constexpr qreal defaultHighestRange = 200;

const QColor outerMinColor(240, 15, 30);
const QColor outerMaxColor(160, 10, 20);
const QColor textColor(207, 204, 204);
const QColor innerColor(41, 40, 40);

constexpr qreal startArcAngle = 50;
constexpr qreal alignArcAngle = 260; // 360 - 2 * startArcAngle

constexpr int arcWidth = 20;

constexpr int valueFontSize = 60;
constexpr int unitFontSize = 30;

constexpr char defaultFontFamily[] = "Orbitron";
}

Gauge::Gauge(QQuickItem *parent)
    : QQuickPaintedItem(parent),
    m_gaugeValue(defaultGaugeValue),
    m_gaugeSize(defaultGaugeSize),
    m_lowestRange(defaultLowestRange),
    m_highestRange(defaultHighestRange),
    m_gaugeUnit("") {}

// Setters with Notifications
void Gauge::setGaugeValue(qreal gaugeValue) {
    if (m_gaugeValue != gaugeValue) {
        m_gaugeValue = gaugeValue;
        emit gaugeValueChanged();
        update(); // Trigger a repaint when the value changes.
    }
}

void Gauge::setGaugeSize(qreal gaugeSize) {
    if (m_gaugeSize != gaugeSize) {
        m_gaugeSize = gaugeSize;
        emit gaugeSizeChanged();
    }
}

void Gauge::setLowestRange(qreal lowestRange) {
    if (m_lowestRange != lowestRange) {
        m_lowestRange = lowestRange;
        emit lowestRangeChanged();
    }
}

void Gauge::setHighestRange(qreal highestRange) {
    if (m_highestRange != highestRange) {
        m_highestRange = highestRange;
        emit highestRangeChanged();
    }
}

void Gauge::setOuterColor(QColor outerColor) {
    if (m_outerColor != outerColor) {
        m_outerColor = outerColor;
        emit outerColorChanged();
    }
}

void Gauge::setGaugeUnit(QString gaugeUnit) {
    if (m_gaugeUnit != gaugeUnit) {
        m_gaugeUnit = gaugeUnit;
        emit gaugeUnitChanged();
    }
}

// Getters
qreal Gauge::getGaugeValue() const { return m_gaugeValue; }
qreal Gauge::getGaugeSize() const { return m_gaugeSize; }
qreal Gauge::getLowestRange() const { return m_lowestRange; }
qreal Gauge::getHighestRange() const { return m_highestRange; }
QString Gauge::getGaugeUnit() const { return m_gaugeUnit; }
QColor Gauge::getOuterColor() const { return m_outerColor; }

void Gauge::paint(QPainter *painter)
{
    QRectF rect = boundingRect();
    painter->setRenderHint(QPainter::Antialiasing);

    drawBackgroundArc(painter, rect);
    drawInnerArc(painter, rect);
    drawValueText(painter, rect);
    drawUnitText(painter, rect);
    drawOuterArc(painter, rect);
}

// Helper Methods
void Gauge::drawBackgroundArc(QPainter *painter, const QRectF &rect)
{
    double startAngle = startArcAngle - 190;
    double spanAngle = 0 - alignArcAngle;
    int pieSize = m_gaugeSize * 0.95;

    painter->save();
    QPen pen(Qt::NoPen);
    painter->setPen(pen);

    // Radial Gradient
    QRadialGradient radialGradient(rect.center(), pieSize / 2);
    radialGradient.setColorAt(0.7, Qt::transparent);
    radialGradient.setColorAt(1.0, outerMaxColor);

    painter->setBrush(radialGradient);
    painter->drawPie(rect.adjusted(pieSize, pieSize, -pieSize, -pieSize), startAngle * 16, spanAngle * 16);
    painter->restore();
}

void Gauge::drawInnerArc(QPainter *painter, const QRectF &rect)
{
    double startAngle = startArcAngle - 190;
    double spanAngle = 0 - alignArcAngle;

    painter->save();
    QPen pen(innerColor, arcWidth, Qt::SolidLine, Qt::FlatCap);
    painter->setPen(pen);
    painter->drawArc(rect.adjusted(arcWidth, arcWidth, -arcWidth, -arcWidth), startAngle * 16, spanAngle * 16);
    painter->restore();
}

void Gauge::drawValueText(QPainter *painter, const QRectF &rect)
{
    painter->save();
    QFont font(defaultFontFamily, valueFontSize);
    painter->setFont(font);
    QPen pen(textColor);
    painter->setPen(pen);

    QRectF textRect = rect.adjusted(m_gaugeSize / 30, m_gaugeSize / 30, -m_gaugeSize / 30, -m_gaugeSize / 5);
    painter->drawText(textRect, Qt::AlignCenter, QString::number(m_gaugeValue));
    painter->restore();
}

void Gauge::drawUnitText(QPainter *painter, const QRectF &rect)
{
    painter->save();
    QFont font(defaultFontFamily, unitFontSize);
    painter->setFont(font);
    QPen pen(textColor);
    painter->setPen(pen);

    QRectF textRect = rect.adjusted(m_gaugeSize / 30, m_gaugeSize / 2, -m_gaugeSize / 30, -m_gaugeSize / 4);
    painter->drawText(textRect, Qt::AlignCenter, m_gaugeUnit);
    painter->restore();
}

void Gauge::drawOuterArc(QPainter *painter, const QRectF &rect)
{
    double startAngle = startArcAngle - 190;
    double spanAngle = ((m_gaugeValue - m_lowestRange) / (m_highestRange - m_lowestRange)) * (-alignArcAngle);

    painter->save();
    QPen pen(outerMinColor, arcWidth, Qt::SolidLine, Qt::FlatCap);
    painter->setPen(pen);
    painter->drawArc(rect.adjusted(arcWidth, arcWidth, -arcWidth, -arcWidth), startAngle * 16, spanAngle * 16);
    painter->restore();
}
