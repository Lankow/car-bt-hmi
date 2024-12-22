#ifndef GAUGE_H
#define GAUGE_H

#include <QObject>
#include <QQuickPaintedItem>

class Gauge : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(qreal gaugeValue READ getgaugeValue WRITE setgaugeValue NOTIFY gaugeValueChanged)
    Q_PROPERTY(qreal gaugeSize READ getGaugeSize WRITE setGaugeSize NOTIFY gaugeSizeChanged)
    Q_PROPERTY(qreal startAngle READ getstartAngle WRITE setstartAngle NOTIFY startAngleChanged)
    Q_PROPERTY(qreal alignAngle READ getalignAngle WRITE setalignAngle NOTIFY alignAngleChanged)
    Q_PROPERTY(qreal lowestRange READ getlowestRange WRITE setlowestRange NOTIFY lowestRangeChanged)
    Q_PROPERTY(qreal highestRange READ gethighestRange WRITE sethighestRange NOTIFY highestRangeChanged)
    Q_PROPERTY(int arcWidth READ getarcWidth WRITE setarcWidth NOTIFY arcWidthChanged)
    Q_PROPERTY(QColor outerColor READ getouterColor WRITE setouterColor NOTIFY outerColorChanged)
    Q_PROPERTY(QColor innerColor READ getinnerColor WRITE setinnerColor NOTIFY innerColorChanged)
    Q_PROPERTY(QColor textColor READ gettextColor WRITE settextColor NOTIFY textColorChanged)
    Q_PROPERTY(QColor backgroundColor READ getbackgroundColor WRITE setbackgroundColor NOTIFY backgroundColorChanged)

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
