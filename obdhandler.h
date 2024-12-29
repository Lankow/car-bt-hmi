#ifndef OBDHANDLER_H
#define OBDHANDLER_H

#include <QObject>
#include <QBluetoothSocket>

class ObdHandler : public QObject {
    Q_OBJECT

public:
    explicit ObdHandler(QObject *parent = nullptr);

    void init();
    qint64 getRPM();
    qint64 getSpeed();

signals:
    void rpmUpdated(qreal  rpm);
    void speedUpdated(qreal  speed);

private:
    QBluetoothSocket *socket;
    void sendCommand(const QString &command);
    qint64 parseHexToDecimal(const QByteArray &data, int startByte, int byteCount);
};

#endif // OBDHANDLER_H
