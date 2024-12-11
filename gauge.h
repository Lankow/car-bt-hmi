#ifndef GAUGE_H
#define GAUGE_H

#include <QObject>
#include <QQuickPaintedItem>

class Gauge : public QQuickPaintedItem
{
    Q_OBJECT

public:
    Gauge(QQuickItem *parent = 0);
    virtual void paint(QPainter *painter);
};

#endif // GAUGE_H
