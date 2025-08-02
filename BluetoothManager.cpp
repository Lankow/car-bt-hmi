#include "BluetoothManager.hpp"
#include <QDebug>

BluetoothManager::BluetoothManager(DeviceModel *model, SettingsManager *settingsManager, QObject *parent)
    : m_model(model), m_settingsManager(settingsManager), QObject(parent),
    m_discoveryAgent(new QBluetoothDeviceDiscoveryAgent(this)),
    m_socket(nullptr),
    m_connectionState(ConnectionState::Initial)
{
    connect(m_discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, &BluetoothManager::deviceDiscovered);
    connect(m_discoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished, this, &BluetoothManager::discoveryFinished);

    createSocket();

    init();
}

void BluetoothManager::setConnectionState(ConnectionState state)
{
    if(m_connectionState != state)
    {
        m_connectionState = state;
        emit connectionStateChanged();
    }
}

void BluetoothManager::init()
{
    QString address = m_settingsManager->getLastDeviceAddress();
    QString name = m_settingsManager->getLastDeviceName();

    if (!address.isEmpty()) {
        qDebug() << "Restoring device:" << name << address;

        m_restoredAddress = QBluetoothAddress(address);
        m_attemptReconnect = true;

        startDiscovery();
    }
}

void BluetoothManager::startDiscovery()
{
    qDebug() << "Starting Bluetooth discovery...";
    m_discoveryAgent->start();
    setConnectionState(ConnectionState::Discovering);
}

void BluetoothManager::stopDiscovery()
{
    qDebug() << "Stoping Bluetooth discovery.";
    m_discoveryAgent->stop();
    if (m_socket->state() != QBluetoothSocket::SocketState::ConnectedState)
    {
        setConnectionState(ConnectionState::Initial);
    }
    else
    {
        setConnectionState(ConnectionState::Connected);
    }
}

void BluetoothManager::deviceDiscovered(const QBluetoothDeviceInfo &device) {
    qDebug() << "Found device:" << device.name() << device.address().toString();
    m_model->addDevice(device);

    if (m_attemptReconnect && device.address() == m_restoredAddress) {
        qDebug() << "Auto-connecting to stored device:" << device.name();
        m_attemptReconnect = false;
        connectToOBD(device);
    }
}

void BluetoothManager::discoveryFinished()
{
    qDebug() << "Discovery Finished.";
    if (m_socket->state() != QBluetoothSocket::SocketState::ConnectedState)
    {
        setConnectionState(ConnectionState::Initial);
    }
    else
    {
        setConnectionState(ConnectionState::Connected);
    }
}

void BluetoothManager::onConnected()
{
    m_obdDevice = m_pendingObdDevice;
    emit activeDeviceNameChanged();

    qDebug() << "Connected to OBD Device!";
    setConnectionState(ConnectionState::Connected);
    stopDiscovery();

    m_settingsManager->setLastDeviceAddress(m_obdDevice.address().toString());
    m_settingsManager->setLastDeviceName(m_obdDevice.name());
}

bool BluetoothManager::sendMessage(const QString &message)
{
    if (m_socket->state() == QBluetoothSocket::SocketState::ConnectedState)
    {
        QString formattedMessage = message + "\r";
        m_socket->write(formattedMessage.toUtf8());
        qDebug() << "Sent:" << formattedMessage;
        return true;
    }
    else
    {
        qDebug() << "Not connected!";
        return false;
    }
}

ConnectionState BluetoothManager::getConnectionState() const {
    return m_connectionState;
}

QString BluetoothManager::getActiveDeviceName() const {
    if (m_connectionState == ConnectionState::Connecting && m_pendingObdDevice.isValid()) {
        return m_pendingObdDevice.name();
    }
    if (m_connectionState == ConnectionState::Connected && m_obdDevice.isValid()) {
        return m_obdDevice.name();
    }
    return "";
}

void BluetoothManager::clearResults()
{
    m_model->clear();
}

void BluetoothManager::connectToOBD(const QBluetoothDeviceInfo &device)
{
    if (!device.isValid()) {
        qWarning() << "Invalid OBD Device!";
        return;
    }

    resetSocket();

    setConnectionState(ConnectionState::Connecting);
    m_pendingObdDevice = device;

    emit activeDeviceNameChanged();

    qDebug() << "Connecting to OBD Device at" << device.address().toString();
    m_socket->connectToService(device.address(), QBluetoothUuid(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB")));
}

void BluetoothManager::onReadyRead()
{
    QByteArray data = m_socket->readAll();
    emit messageReceived(data);
}

void BluetoothManager::onErrorOccurred(QBluetoothSocket::SocketError error)
{
    qDebug() << "Bluetooth Error:" << error;
    m_pendingObdDevice = QBluetoothDeviceInfo();
    setConnectionState(ConnectionState::Error);
}

void BluetoothManager::onDisconnected()
{
    qDebug() << "OBD Device disconnected!";
    setConnectionState(ConnectionState::Disconnected);
}

void BluetoothManager::createSocket()
{
    m_socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol, this);

    connect(m_socket, &QBluetoothSocket::connected, this, &BluetoothManager::onConnected);
    connect(m_socket, &QBluetoothSocket::readyRead, this, &BluetoothManager::onReadyRead);
    connect(m_socket, &QBluetoothSocket::errorOccurred, this, &BluetoothManager::onErrorOccurred);
    connect(m_socket, &QBluetoothSocket::disconnected, this, &BluetoothManager::onDisconnected);
}

void BluetoothManager::resetSocket()
{
    if (m_socket) {
        m_socket->disconnectFromService();
        m_socket->close();
        m_socket->deleteLater();
        m_socket = nullptr;
    }

    createSocket();
}
