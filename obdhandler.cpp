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

    QObject::connect(socket, &QBluetoothSocket::errorOccurred, [](QBluetoothSocket::SocketError error) {
        qDebug() << "Socket error:" << error;
    });

    socket->connectToService(QBluetoothAddress("XX:XX:XX:XX:XX:XX"), 2); // TODO: OBD-II Interface Bluetooth Mac Address extraction
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
    hexValue.replace(" ", "");

    bool ok;
    return hexValue.toUInt(&ok, 16);
}

qint64 ObdHandler::getRPM() {
    sendCommand("010C");

    QObject::connect(socket, &QBluetoothSocket::readyRead, this, [this]() {
        QByteArray response = socket->readAll();

        if (response.startsWith("41 0C")) {
            qint64 rawRPM = parseHexToDecimal(response, 6, 5);
            qint64 rpm = (rawRPM / 4);
            qDebug() << "RPM: " << rpm;
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
            qint64 speed = parseHexToDecimal(response, 6, 2);
            qDebug() << "Speed: " << speed;
            emit speedUpdated(speed);
        }
    });

    return 0;
}
