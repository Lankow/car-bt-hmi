#ifndef STATEINDICATOR_HPP
#define STATEINDICATOR_HPP

#include <QQuickPaintedItem>
#include <QTimer>
#include "ConnectionState.hpp"

using ConnectionState = ConnectionStateHelper::ConnectionState;

class StateIndicator : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(ConnectionState connectionState READ getConnectionState WRITE setConnectionState NOTIFY connectionStateChanged)
    Q_PROPERTY(QString stateText READ getStateText NOTIFY connectionStateChanged)
    Q_PROPERTY(int size READ getSize WRITE setSize NOTIFY sizeChanged)

public:
    explicit StateIndicator(QQuickItem* parent = nullptr);

    ConnectionState getConnectionState() const;
    int getSize() const { return m_size; }
    QString getStateText() const;

    void setConnectionState(ConnectionState connectionState);
    void setSize(int size);

    void paint(QPainter* painter) override;

signals:
    void connectionStateChanged();
    void sizeChanged();

private:
    void connectionStateToColor();
    ConnectionState m_connectionState {ConnectionState::Initial};
    int m_size = 50;

    QColor m_currentColor;
    QTimer m_timer;
    qreal m_blinkPhase = 0.0;
};

#endif // STATEINDICATOR_HPP
