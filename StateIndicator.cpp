#include "StateIndicator.hpp"
#include <QPainter>

const QColor initialColor(128, 128, 128);
const QColor connectedColor(40, 195, 70);
const QColor connectingColor(70, 130, 180);
const QColor discoveringColor(255, 200, 0);
const QColor disconnectedColor(255, 140, 0);
const QColor errorColor(160, 10, 20);

StateIndicator::StateIndicator(QQuickItem* parent)
    : QQuickPaintedItem(parent)
{
    setWidth(m_size);
    setHeight(m_size);
    m_currentColor = initialColor;

    m_timer.setInterval(24);
    connect(&m_timer, &QTimer::timeout, this, [this]() {
        m_blinkPhase += 0.1;
        if (m_blinkPhase > 2 * M_PI)
            m_blinkPhase -= 2 * M_PI;
        update();
    });
    m_timer.start();
}

void StateIndicator::setState(ConnectionState state)
{
    if (state != m_state) {
        m_state = state;
        stateToColor();
        update();
        emit stateChanged();
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

void StateIndicator::stateToColor()
{
    switch (m_state) {
    case ConnectionState::Initial:
        m_currentColor = initialColor;
    case ConnectionState::Discovering:
        m_currentColor = discoveringColor;
        break;
    case ConnectionState::Connected:
        m_currentColor = connectedColor;
        break;
    case ConnectionState::Connecting:
        m_currentColor = connectingColor;
        break;
    case ConnectionState::Error:
        m_currentColor = errorColor;
        break;
    case ConnectionState::Disconnected:
    default:
        m_currentColor = disconnectedColor;
        break;
    }
}
