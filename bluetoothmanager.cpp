#include "bluetoothmanager.hpp"
#include <QDebug>

BluetoothManager::BluetoothManager(QObject *parent)
    : QObject(parent), m_discoveryAgent(new QBluetoothDeviceDiscoveryAgent(this)),
    m_socket(new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol, this))
{
    connect(m_discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, &BluetoothManager::deviceDiscovered);
    connect(m_discoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished, this, &BluetoothManager::discoveryFinished);

    connect(m_socket, &QBluetoothSocket::connected, this, &BluetoothManager::onConnected);
    connect(m_socket, &QBluetoothSocket::readyRead, this, &BluetoothManager::onReadyRead);
    connect(m_socket, &QBluetoothSocket::errorOccurred, this, &BluetoothManager::onErrorOccurred);
}

void BluetoothManager::startDiscovery()
{
    qDebug() << "Starting Bluetooth discovery...";
    m_discoveryAgent->start();
}

void BluetoothManager::deviceDiscovered(const QBluetoothDeviceInfo &device)
{
    qDebug() << "Found device:" << device.name() << device.address().toString();

    if (device.name() == "OBDII-ESP")  // Match ESP32 Bluetooth name
    {
        m_esp32Device = device;
        emit deviceFound(device.name());
        m_discoveryAgent->stop();  // Stop scanning
    }
}

void BluetoothManager::discoveryFinished()
{
    if (!m_esp32Device.isValid())
    {
        qDebug() << "ESP32 not found.";
        return;
    }

    qDebug() << "Connecting to ESP32...";
    m_socket->connectToService(m_esp32Device.address(), QBluetoothUuid(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB")));
}

void BluetoothManager::onConnected()
{
    qDebug() << "Connected to ESP32!";
    m_connected = true;
    emit connectedChanged();
}

void BluetoothManager::sendMessage(const QString &message)
{
    if (m_socket->state() == QBluetoothSocket::SocketState::ConnectedState)
    {
        QString formattedMessage = message + "\r";
        m_socket->write(formattedMessage.toUtf8());
        qDebug() << "Sent:" << formattedMessage;
    }
    else
    {
        qDebug() << "Not connected!";
    }
}
void BluetoothManager::connectToESP32()
{
    if (!m_esp32Device.isValid()) {
        qWarning() << "No ESP32 device found!";
        return;
    }

    qDebug() << "Connecting to ESP32 at" << m_esp32Device.address().toString();

    // Ensure socket is not already connected
    if (m_socket->state() == QBluetoothSocket::SocketState::ConnectedState) {
        qDebug() << "Already connected to ESP32.";
        return;
    }

    // Connect to ESP32 Bluetooth Serial (RFCOMM)
    m_socket->connectToService(m_esp32Device.address(), QBluetoothUuid(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB")));

    qDebug() << "Attempting to connect...";
}

void BluetoothManager::onReadyRead()
{
    QByteArray data = m_socket->readAll();
    qDebug() << "Received from ESP32:" << QString::fromUtf8(data);
    emit messageReceived(QString::fromUtf8(data));
}

void BluetoothManager::onErrorOccurred(QBluetoothSocket::SocketError error)
{
    qDebug() << "Bluetooth Error:" << error;
}
