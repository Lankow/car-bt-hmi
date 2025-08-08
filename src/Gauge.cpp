#include "Gauge.hpp"
#include <QPainter>
#include <QFont>
#include <QRadialGradient>

namespace {
constexpr qreal kDefaultValue = 0;
constexpr qreal kDefaultSize = 500;
constexpr qreal kDefaultMinValue = 0;
constexpr qreal kDefaultMaxValue = 200;

constexpr qreal kStartAngle = 50;
constexpr qreal kSweepAngle = 260;

constexpr int kArcWidth = 20;
constexpr int kValueFontSize = 55;
constexpr int kUnitFontSize = 25;
constexpr char kFontFamily[] = "Orbitron";

const QColor kOuterMinColor(40, 195, 70);
const QColor kOuterMaxColor(160, 10, 20);
const QColor kTextColor(207, 204, 204);
const QColor kInnerArcColor(41, 40, 40);
}

Gauge::Gauge(QQuickItem *parent)
    : QQuickPaintedItem(parent),
    m_value(kDefaultValue),
    m_size(kDefaultSize),
    m_minValue(kDefaultMinValue),
    m_maxValue(kDefaultMaxValue),
    m_unit("")
{}

void Gauge::setValue(qreal value)
{
    value = qBound(m_minValue, value, m_maxValue);
    if (!qFuzzyCompare(m_value, value)) {
        m_value = value;
        emit valueChanged();
        update();
    }
}

void Gauge::setSize(qreal size)
{
    if (!qFuzzyCompare(m_size, size)) {
        m_size = size;
        update();
        emit sizeChanged();
    }
}

void Gauge::setMinValue(qreal minValue)
{
    if (!qFuzzyCompare(m_minValue, minValue)) {
        m_minValue = minValue;
        update();
        emit minValueChanged();
    }
}

void Gauge::setMaxValue(qreal maxValue)
{
    if (!qFuzzyCompare(m_maxValue, maxValue)) {
        m_maxValue = maxValue;
        update();
        emit maxValueChanged();
    }
}

void Gauge::setUnit(QString unit)
{
    if (m_unit != unit) {
        m_unit = std::move(unit);
        update();
        emit unitChanged();
    }
}

void Gauge::setEnabled(bool enabled) {
    if (m_enabled != enabled) {
        m_enabled = enabled;
        emit enabledChanged();
        update();
    }
}

qreal Gauge::getValue() const { return m_value; }
qreal Gauge::getSize() const { return m_size; }
qreal Gauge::getMinValue() const { return m_minValue; }
qreal Gauge::getMaxValue() const { return m_maxValue; }
QString Gauge::getUnit() const { return m_unit; }
bool Gauge::getEnabled() const { return m_enabled; }

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

void Gauge::drawBackgroundArc(QPainter *painter, const QRectF &rect)
{
    painter->save();

    QRadialGradient gradient(rect.center(), rect.width() / 2);
    gradient.setColorAt(0.7, Qt::transparent);
    gradient.setColorAt(1.0, getOuterColor());

    painter->setBrush(gradient);
    painter->setPen(Qt::NoPen);
    painter->drawPie(rect.adjusted(m_size * 0.05, m_size * 0.05, -m_size * 0.05, -m_size * 0.05),
                     (kStartAngle - 190) * 16, -kSweepAngle * 16);
    painter->restore();
}

void Gauge::drawInnerArc(QPainter *painter, const QRectF &rect)
{
    painter->save();
    QPen pen(kInnerArcColor, kArcWidth, Qt::SolidLine, Qt::FlatCap);
    painter->setPen(pen);
    painter->drawArc(rect.adjusted(kArcWidth, kArcWidth, -kArcWidth, -kArcWidth),
                     (kStartAngle - 190) * 16, -kSweepAngle * 16);
    painter->restore();
}

void Gauge::drawOuterArc(QPainter *painter, const QRectF &rect)
{
    painter->save();
    QPen pen(getOuterColor(), kArcWidth, Qt::SolidLine, Qt::FlatCap);
    painter->setPen(pen);

    if (qFuzzyCompare(m_maxValue, m_minValue)) {
        painter->restore();
        return;
    }

    const qreal valueRatio = (m_value - m_minValue) / (m_maxValue - m_minValue);
    const qreal sweep = valueRatio * -kSweepAngle;

    painter->drawArc(rect.adjusted(kArcWidth, kArcWidth, -kArcWidth, -kArcWidth),
                     (kStartAngle - 190) * 16, sweep * 16);
    painter->restore();
}

void Gauge::drawValueText(QPainter *painter, const QRectF &rect)
{
    painter->save();
    painter->setFont(QFont(kFontFamily, kValueFontSize));
    painter->setPen(kTextColor);

    QRectF textRect = rect.adjusted(m_size / 30, m_size / 30, -m_size / 30, -m_size / 5);
    QString valueText = m_enabled ? QString::number(static_cast<int>(m_value)) : "--";
    painter->drawText(textRect, Qt::AlignCenter, valueText);
    painter->restore();
}

void Gauge::drawUnitText(QPainter *painter, const QRectF &rect)
{
    painter->save();
    painter->setFont(QFont(kFontFamily, kUnitFontSize));
    painter->setPen(kTextColor);

    QRectF unitRect = rect.adjusted(m_size / 30, m_size / 2, -m_size / 30, -m_size / 4);
    painter->drawText(unitRect, Qt::AlignCenter, m_unit);
    painter->restore();
}

QColor Gauge::getOuterColor() const
{
    if (qFuzzyCompare(m_maxValue, m_minValue)) {
        return kOuterMinColor;
    }

    const qreal t = (m_value - m_minValue) / (m_maxValue - m_minValue);
    const int r = kOuterMinColor.red() + t * (kOuterMaxColor.red() - kOuterMinColor.red());
    const int g = kOuterMinColor.green() + t * (kOuterMaxColor.green() - kOuterMinColor.green());
    const int b = kOuterMinColor.blue() + t * (kOuterMaxColor.blue() - kOuterMinColor.blue());
    return QColor(r, g, b);
}
