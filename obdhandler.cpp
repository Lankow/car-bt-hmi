#include "obdhandler.h"
#include <QDebug>
#include <QTimer>

ObdHandler::ObdHandler(QObject *parent)
    : QObject(parent), socket(nullptr) {}

void ObdHandler::connectToELM327() {
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);

    QObject::connect(socket, &QBluetoothSocket::connected, []() {
        qDebug() << "Connected to ELM327 device";
    });

    QObject::connect(socket, &QBluetoothSocket::readyRead, this, [this]() {
        QByteArray data = socket->readAll();
        qDebug() << "Received:" << data;
    });

    QObject::connect(socket, &QBluetoothSocket::errorOccurred, [](QBluetoothSocket::SocketError error) {
        qDebug() << "Socket error:" << error;
    });

    socket->connectToService(QBluetoothAddress("XX:XX:XX:XX:XX:XX"), 1); // OBD2 Interface BT Mac Address
}

void ObdHandler::sendCommand(const QString &command) {
    QByteArray byteArray = QByteArray(command.toUtf8() + "\r", command.length() + 1);

    if (socket && socket->isOpen()) {
        qDebug() << "Sending command as bytes:" << byteArray.toHex(' ');
        socket->write(byteArray);
    } else {
        qWarning() << "Socket not connected!";
    }
}

qint64 ObdHandler::parseHexToDecimal(const QByteArray &data, int startByte, int byteCount) {
    if (data.size() < startByte + byteCount) {
        qWarning() << "Invalid data length for parsing!";
        return -1;
    }

    QByteArray hexValue = data.mid(startByte, byteCount);
    bool ok;
    return hexValue.toUInt(&ok, 16);
}

qint64 ObdHandler::getRPM() {
    sendCommand("010C");

    QObject::connect(socket, &QBluetoothSocket::readyRead, this, [this]() {
        QByteArray response = socket->readAll();

        if (response.startsWith("41 0C")) {
            qint64 rawRPM = parseHexToDecimal(response, 2, 2);
            qint64 rpm = (rawRPM / 4);
            emit rpmUpdated(rpm);
        }
    });

    return 0;
}

qint64 ObdHandler::getSpeed() {
    sendCommand("010D");

    QObject::connect(socket, &QBluetoothSocket::readyRead, this, [this]() {
        QByteArray response = socket->readAll();

        if (response.startsWith("41 0D")) {
            qint64 speed = parseHexToDecimal(response, 2, 1);
            emit speedUpdated(speed);
        }
    });

    return 0;
}
