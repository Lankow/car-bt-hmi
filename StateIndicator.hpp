#pragma once

#include <QQuickPaintedItem>
#include <QTimer>
#include "ConnectionState.hpp"

using ConnectionState = ConnectionStateHelper::ConnectionState;

class StateIndicator : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(ConnectionState state READ getState WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(int size READ getSize WRITE setSize NOTIFY sizeChanged)

public:
    explicit StateIndicator(QQuickItem* parent = nullptr);

    ConnectionState getState() const { return m_state; }
    int getSize() const { return m_size; }

    void setState(ConnectionState state);
    void setSize(int size);

    void paint(QPainter* painter) override;

signals:
    void stateChanged();
    void sizeChanged();

private:
    void stateToColor();
    ConnectionState m_state;
    int m_size = 50;

    QColor m_currentColor;
    QTimer m_timer;
    qreal m_blinkPhase = 0.0;
};
