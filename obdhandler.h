#ifndef OBDHANDLER_H
#define OBDHANDLER_H

#include <QObject>
#include <QBluetoothSocket>

class ObdHandler : public QObject {
    Q_OBJECT

public:
    explicit ObdHandler(QObject *parent = nullptr);

    void connectToELM327();
    qint64 getRPM();
    qint64 getSpeed();
    qint64 getOdometer();

signals:
    void rpmUpdated(qint64 rpm);
    void speedUpdated(qint64 speed);
    void odometerUpdated(qint64 odometer);

private:
    QBluetoothSocket *socket;
    void sendCommand(const QString &command);
    qint64 parseHexToDecimal(const QByteArray &data, int startByte, int byteCount);
};

#endif // OBDHANDLER_H
