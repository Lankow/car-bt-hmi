#include "gauge.h"
#include <QPainter>

// Constants
namespace {
constexpr qreal defaultValue = 0;
constexpr qreal defaultSize = 500;

constexpr qreal defaultMinValue = 0;
constexpr qreal defaultMaxValue = 200;

const QColor outerMinColor(40, 195, 70);
const QColor outerMaxColor(160, 10, 20);

const QColor textColor(207, 204, 204);
const QColor innerColor(41, 40, 40);

constexpr qreal startArcAngle = 50;
constexpr qreal alignArcAngle = 260; // 360 - 2 * startArcAngle

constexpr int arcWidth = 20;

constexpr int valueFontSize = 55;
constexpr int unitFontSize = 25;

constexpr char defaultFontFamily[] = "Orbitron";
}

Gauge::Gauge(QQuickItem *parent)
    : QQuickPaintedItem(parent),
    m_value(defaultValue),
    m_size(defaultSize),
    m_minValue(defaultMinValue),
    m_maxValue(defaultMaxValue),
    m_unit("") {}

// Setters with Notifications
void Gauge::setValue(qreal value) {
    if (m_value != value && value >= m_minValue && value <= m_maxValue) {
        m_value = value;
        emit valueChanged();
        update(); // Trigger a repaint when the value changes.
    }
}

void Gauge::setSize(qreal size) {
    if (m_size != size) {
        m_size = size;
        emit sizeChanged();
    }
}

void Gauge::setMinValue(qreal minValue) {
    if (m_minValue != minValue) {
        m_minValue = minValue;
        emit minValueChanged();
    }
}

void Gauge::setMaxValue(qreal maxValue) {
    if (m_maxValue != maxValue) {
        m_maxValue = maxValue;
        emit maxValueChanged();
    }
}

void Gauge::setUnit(QString unit) {
    if (m_unit != unit) {
        m_unit = unit;
        emit unitChanged();
    }
}

// Getters
qreal Gauge::getValue() const { return m_value; }
qreal Gauge::getSize() const { return m_size; }
qreal Gauge::getMinValue() const { return m_minValue; }
qreal Gauge::getMaxValue() const { return m_maxValue; }
QString Gauge::getUnit() const { return m_unit; }

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
    int pieSize = m_size * 0.95;

    painter->save();
    QPen pen(Qt::NoPen);
    painter->setPen(pen);

    // Radial Gradient
    QColor outerColor = getOuterColor();
    QRadialGradient radialGradient(rect.center(), pieSize / 2);
    radialGradient.setColorAt(0.7, Qt::transparent);
    radialGradient.setColorAt(1.0, outerColor);

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

    QRectF textRect = rect.adjusted(m_size / 30, m_size / 30, -m_size / 30, -m_size / 5);
    painter->drawText(textRect, Qt::AlignCenter, QString::number(m_value));
    painter->restore();
}

void Gauge::drawUnitText(QPainter *painter, const QRectF &rect)
{
    painter->save();
    QFont font(defaultFontFamily, unitFontSize);
    painter->setFont(font);
    QPen pen(textColor);
    painter->setPen(pen);

    QRectF textRect = rect.adjusted(m_size / 30, m_size / 2, -m_size / 30, -m_size / 4);
    painter->drawText(textRect, Qt::AlignCenter, m_unit);
    painter->restore();
}

void Gauge::drawOuterArc(QPainter *painter, const QRectF &rect)
{
    double startAngle = startArcAngle - 190;
    double valuePercentage = (m_value - m_minValue) / (m_maxValue - m_minValue);
    double spanAngle = ( valuePercentage * (-alignArcAngle));

    QColor outerColor = getOuterColor();

    painter->save();
    QPen pen(outerColor, arcWidth, Qt::SolidLine, Qt::FlatCap);
    painter->setPen(pen);
    painter->drawArc(rect.adjusted(arcWidth, arcWidth, -arcWidth, -arcWidth), startAngle * 16, spanAngle * 16);
    painter->restore();
}

QColor Gauge::getOuterColor(){
    double valuePercentage = (m_value - m_minValue) / (m_maxValue - m_minValue);

    int r = outerMinColor.red() + (valuePercentage * (outerMaxColor.red()-outerMinColor.red()));
    int g = outerMinColor.green() + (valuePercentage * (outerMaxColor.green()-outerMinColor.green()));
    int b = outerMinColor.blue() + (valuePercentage * (outerMaxColor.blue()-outerMinColor.blue()));

    return QColor(r,g,b);
}
