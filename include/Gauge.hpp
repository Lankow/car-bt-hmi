#ifndef GAUGE_HPP
#define GAUGE_HPP

#include <QObject>
#include <QQuickPaintedItem>
#include <QColor>

class Gauge : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(qreal value READ getValue WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(qreal size READ getSize WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(qreal minValue READ getMinValue WRITE setMinValue NOTIFY minValueChanged)
    Q_PROPERTY(qreal maxValue READ getMaxValue WRITE setMaxValue NOTIFY maxValueChanged)
    Q_PROPERTY(QString unit READ getUnit WRITE setUnit NOTIFY unitChanged)

public:
    explicit Gauge(QQuickItem *parent = nullptr);
    void paint(QPainter *painter) override;

    // Getters
    qreal getValue() const;
    qreal getSize() const;
    qreal getMinValue() const;
    qreal getMaxValue() const;
    QString getUnit() const;

    // Setters
    void setValue(qreal value);
    void setSize(qreal size);
    void setMinValue(qreal minValue);
    void setMaxValue(qreal maxValue);
    void setUnit(QString unit);

signals:
    void valueChanged();
    void sizeChanged();
    void minValueChanged();
    void maxValueChanged();
    void unitChanged();

private:
    qreal m_value = 0;
    qreal m_size = 500;
    qreal m_minValue = 0;
    qreal m_maxValue = 200;
    QString m_unit;

    void drawBackgroundArc(QPainter *painter, const QRectF &rect);
    void drawInnerArc(QPainter *painter, const QRectF &rect);
    void drawValueText(QPainter *painter, const QRectF &rect);
    void drawUnitText(QPainter *painter, const QRectF &rect);
    void drawOuterArc(QPainter *painter, const QRectF &rect);
    QColor getOuterColor() const;
};

#endif // GAUGE_HPP
