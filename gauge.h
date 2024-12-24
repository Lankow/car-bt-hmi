#ifndef GAUGE_H
#define GAUGE_H

#include <QObject>
#include <QQuickPaintedItem>
#include <QColor>

/**
 * @class Gauge
 * @brief A custom gauge widget for Qt Quick with configurable properties and visual styles.
 */
class Gauge : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(qreal gaugeValue READ getGaugeValue WRITE setGaugeValue NOTIFY gaugeValueChanged)
    Q_PROPERTY(qreal gaugeSize READ getGaugeSize WRITE setGaugeSize NOTIFY gaugeSizeChanged)
    Q_PROPERTY(qreal lowestRange READ getLowestRange WRITE setLowestRange NOTIFY lowestRangeChanged)
    Q_PROPERTY(qreal highestRange READ getHighestRange WRITE setHighestRange NOTIFY highestRangeChanged)
    Q_PROPERTY(QString gaugeUnit READ getGaugeUnit WRITE setGaugeUnit NOTIFY gaugeUnitChanged)

public:
    explicit Gauge(QQuickItem *parent = nullptr); ///< Constructor
    virtual void paint(QPainter *painter) override; ///< Paint function to draw the gauge.

    // Getters
    qreal getGaugeValue() const;
    qreal getGaugeSize() const;
    qreal getLowestRange() const;
    qreal getHighestRange() const;
    QString getGaugeUnit() const;

    // Setters
    void setGaugeValue(qreal gaugeValue);
    void setGaugeSize(qreal gaugeSize);
    void setLowestRange(qreal lowestRange);
    void setHighestRange(qreal highestRange);
    void setGaugeUnit(QString gaugeUnit);

signals:
    void gaugeValueChanged();
    void gaugeSizeChanged();
    void lowestRangeChanged();
    void highestRangeChanged();
    void gaugeUnitChanged();

private:
    qreal m_gaugeSize; ///< Size of the gauge.
    qreal m_lowestRange; ///< Lowest range of the gauge.
    qreal m_highestRange; ///< Highest range of the gauge.
    qreal m_gaugeValue; ///< Current value displayed on the gauge.
    QString m_gaugeUnit; ///< Unit displayed on the gauge.

    void drawBackgroundArc(QPainter *painter, const QRectF &rect);
    void drawInnerArc(QPainter *painter, const QRectF &rect);
    void drawValueText(QPainter *painter, const QRectF &rect);
    void drawUnitText(QPainter *painter, const QRectF &rect);
    void drawOuterArc(QPainter *painter, const QRectF &rect);

    QColor getOuterColor();
};

#endif // GAUGE_H
