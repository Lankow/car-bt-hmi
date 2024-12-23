#ifndef GAUGE_H
#define GAUGE_H

#include <QObject>
#include <QQuickPaintedItem>

class Gauge : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(qreal gaugeValue READ getGaugeValue WRITE setGaugeValue NOTIFY gaugeValueChanged)
    Q_PROPERTY(qreal gaugeSize READ getGaugeSize WRITE setGaugeSize NOTIFY gaugeSizeChanged)
    Q_PROPERTY(qreal startAngle READ getStartAngle WRITE setStartAngle NOTIFY startAngleChanged)
    Q_PROPERTY(qreal alignAngle READ getAlignAngle WRITE setAlignAngle NOTIFY alignAngleChanged)
    Q_PROPERTY(qreal lowestRange READ getLowestRange WRITE setLowestRange NOTIFY lowestRangeChanged)
    Q_PROPERTY(qreal highestRange READ getHighestRange WRITE setHighestRange NOTIFY highestRangeChanged)
    Q_PROPERTY(int arcWidth READ getArcWidth WRITE setArcWidth NOTIFY arcWidthChanged)
    Q_PROPERTY(QColor outerColor READ getOuterColor WRITE setOuterColor NOTIFY outerColorChanged)
    Q_PROPERTY(QColor innerColor READ getInnerColor WRITE setInnerColor NOTIFY innerColorChanged)
    Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor NOTIFY textColorChanged)
    Q_PROPERTY(QColor backgroundColor READ getBackgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)

public:
    Gauge(QQuickItem *parent = 0);
    virtual void paint(QPainter *painter);

    qreal getGaugeValue();
    qreal getGaugeSize();
    qreal getStartAngle();
    qreal getAlignAngle();
    qreal getLowestRange();
    qreal getHighestRange();
    int getArcWidth();
    QColor getOuterColor();
    QColor getInnerColor();
    QColor getTextColor();
    QColor getBackgroundColor();

    void setGaugeValue(qreal gaugeValue);
    void setGaugeSize(qreal gaugeSize);
    void setStartAngle(qreal startAngle);
    void setAlignAngle(qreal alignAngle);
    void setLowestRange(qreal lowestRange);
    void setHighestRange(qreal highestRange);
    void setArcWidth(int arcWidth);
    void setOuterColor(QColor outerColor);
    void setInnerColor(QColor innerColor);
    void setTextColor(QColor textColor);
    void setBackgroundColor(QColor backgroundColor);

signals:
    void gaugeSizeChanged();
    void startAngleChanged();
    void alignAngleChanged();
    void lowestRangeChanged();
    void highestRangeChanged();
    void gaugeValueChanged();
    void arcWidthChanged();
    void outerColorChanged();
    void innerColorChanged();
    void textColorChanged();
    void backgroundColorChanged();

private:
    qreal m_gaugeSize;
    qreal m_startAngle;
    qreal m_alignAngle;
    qreal m_lowestRange;
    qreal m_highestRange;
    qreal m_gaugeValue;
    int m_arcWidth;
    QColor m_outerColor;
    QColor m_innerColor;
    QColor m_textColor;
    QColor m_backgroundColor;
};

#endif // GAUGE_H
