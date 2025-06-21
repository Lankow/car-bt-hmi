#include "StateIndicator.hpp"
#include <QPainter>

namespace
{
const QColor InitialColor(100, 100, 100);
const QColor ConnectedColor(40, 195, 70);
const QColor ConnectingColor(70, 130, 180);
const QColor DiscoveringColor(255, 200, 0);
const QColor DisconnectedColor(255, 140, 0);
const QColor ErrorColor(160, 10, 20);
}

StateIndicator::StateIndicator(QQuickItem* parent)
    : QQuickPaintedItem(parent),
    m_currentColor(InitialColor)
{
    setWidth(m_size);
    setHeight(m_size);
    m_currentColor = InitialColor;

    m_timer.setInterval(24);
    connect(&m_timer, &QTimer::timeout, this, [this]() {
        m_blinkPhase += 0.1;
        if (m_blinkPhase > 2 * M_PI)
            m_blinkPhase -= 2 * M_PI;
        update();
    });
    m_timer.start();
}

ConnectionState StateIndicator::getConnectionState() const
{
    return m_connectionState;
}


void StateIndicator::setConnectionState(ConnectionState state)
{
    if (state != m_connectionState) {
        m_connectionState = state;
        connectionStateToColor();
        update();
        emit connectionStateChanged();
    }
}

void StateIndicator::setSize(int size)
{
    if (size != m_size) {
        m_size = size;
        setWidth(size);
        setHeight(size);
        update();
        emit sizeChanged();
    }
}

void StateIndicator::paint(QPainter* painter)
{
    QRectF rect = boundingRect();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->save();

    qreal blinkFactor = 0.4 + 0.3 * std::sin(m_blinkPhase);
    QColor dynamicColor = m_currentColor.darker(150 + int((1.0 - blinkFactor) * 100));

    QRadialGradient gradient(rect.center(), rect.width() / 2);
    gradient.setColorAt(0.6, dynamicColor);
    gradient.setColorAt(0.95, dynamicColor.darker(180));

    painter->setBrush(gradient);
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(rect);

    painter->restore();
}

void StateIndicator::connectionStateToColor()
{
    switch (m_connectionState) {
    case ConnectionState::Initial:
        m_currentColor = InitialColor;
        break;
    case ConnectionState::Discovering:
        m_currentColor = DiscoveringColor;
        break;
    case ConnectionState::Connected:
        m_currentColor = ConnectedColor;
        break;
    case ConnectionState::Connecting:
        m_currentColor = ConnectingColor;
        break;
    case ConnectionState::Error:
        m_currentColor = ErrorColor;
        break;
    case ConnectionState::Disconnected:
    default:
        m_currentColor = DisconnectedColor;
        break;
    }
}

QString StateIndicator::getStateText() const {
    switch (m_connectionState) {
    case ConnectionState::Initial: return "Initial";
    case ConnectionState::Discovering: return "Discovering";
    case ConnectionState::Connected: return "Connected";
    case ConnectionState::Connecting: return "Connecting";
    case ConnectionState::Error: return "Error";
    case ConnectionState::Disconnected: return "Disconnected";
    default: return "Unknown";
    }
}
