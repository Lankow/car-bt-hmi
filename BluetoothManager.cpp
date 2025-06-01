#include "BluetoothManager.hpp"
#include <QDebug>

BluetoothManager::BluetoothManager(DeviceModel *model, QObject *parent)
    : m_model(model), QObject(parent), m_discoveryAgent(new QBluetoothDeviceDiscoveryAgent(this)),
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

void BluetoothManager::stopDiscovery()
{
    m_discoveryAgent->stop();
}

void BluetoothManager::deviceDiscovered(const QBluetoothDeviceInfo &device) {
    qDebug() << "Found device:" << device.name() << device.address().toString();
    m_model->addDevice(device);
}

void BluetoothManager::discoveryFinished()
{
    if (!m_obdDevice.isValid())
    {
        qDebug() << "OBD Device not found.";
        return;
    }

    qDebug() << "Connecting to OBD Device...";
    m_socket->connectToService(m_obdDevice.address(), QBluetoothUuid(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB")));
}

void BluetoothManager::onConnected()
{
    qDebug() << "Connected to OBD Device!";
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

void BluetoothManager::connectToOBD(const QBluetoothDeviceInfo &device)
{
    m_obdDevice = device;

    if (!m_obdDevice.isValid()) {
        qWarning() << "No OBD Device found!";
        return;
    }

    qDebug() << "Connecting to OBD Device at" << m_obdDevice.address().toString();

    if (m_socket->state() == QBluetoothSocket::SocketState::ConnectedState) {
        qDebug() << "Already connected to OBD Device.";
        return;
    }

    m_socket->connectToService(m_obdDevice.address(), QBluetoothUuid(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB")));
}

void BluetoothManager::onReadyRead()
{
    QByteArray data = m_socket->readAll();
    qDebug() << "Received from OBD Device:" << QString::fromUtf8(data);
    emit messageReceived(QString::fromUtf8(data));
}

void BluetoothManager::onErrorOccurred(QBluetoothSocket::SocketError error)
{
    qDebug() << "Bluetooth Error:" << error;
}
