#pragma once

#include <QQuickPaintedItem>
#include <QTimer>

class StateIndicator : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(int state READ getState WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(int size READ getSize WRITE setSize NOTIFY sizeChanged)

public:
    explicit StateIndicator(QQuickItem* parent = nullptr);

    int getState() const { return m_state; }
    int getSize() const { return m_size; }

    void setState(int state);
    void setSize(int size);

    void paint(QPainter* painter) override;

signals:
    void stateChanged();
    void sizeChanged();

private:
    int m_state = 0;
    int m_size = 50;

    QColor m_currentColor;
    QTimer m_timer;
    qreal m_blinkPhase = 0.0;
};
