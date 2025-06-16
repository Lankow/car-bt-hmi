#include "StateIndicator.hpp"
#include <QPainter>

StateIndicator::StateIndicator(QQuickItem* parent)
    : QQuickPaintedItem(parent)
{
    setWidth(m_size);
    setHeight(m_size);
}

void StateIndicator::setState(int state)
{
    if (state != m_state) {
        m_state = state;
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
}
