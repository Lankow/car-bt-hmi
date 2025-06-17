#include "StateIndicator.hpp"
#include <QPainter>

const QColor connectedColor(40, 195, 70);
const QColor disconnectedColor(160, 10, 20);

StateIndicator::StateIndicator(QQuickItem* parent)
    : QQuickPaintedItem(parent)
{
    setWidth(m_size);
    setHeight(m_size);
    m_currentColor = disconnectedColor;

    m_timer.setInterval(16);
    connect(&m_timer, &QTimer::timeout, this, [this]() {
        m_blinkPhase += 0.1;
        if (m_blinkPhase > 2 * M_PI)
            m_blinkPhase -= 2 * M_PI;
        update();
    });
    m_timer.start();
}

void StateIndicator::setState(int state)
{
    if (state != m_state) {
        m_state = state;
        m_currentColor = m_state == 1 ? connectedColor : disconnectedColor;
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
    gradient.setColorAt(0.5, dynamicColor);
    gradient.setColorAt(0.8, dynamicColor.darker(160));
    gradient.setColorAt(1.0, dynamicColor.darker(200));

    painter->setBrush(gradient);
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(rect);

    painter->restore();
}
