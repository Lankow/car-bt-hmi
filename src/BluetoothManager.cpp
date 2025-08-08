#include <QBluetoothPermission>
#include <QCoreApplication>
#include <QDebug>
#include <QPermission>
#include "BluetoothManager.hpp"

BluetoothManager::BluetoothManager(DeviceModel *model, SettingsManager *settingsManager, DataProvider *dataProvider, QObject *parent)
    : m_model(model), m_settingsManager(settingsManager), m_dataProvider(dataProvider), QObject(parent),
    m_discoveryAgent(new QBluetoothDeviceDiscoveryAgent(this)),
    m_socket(nullptr),
    m_connectionState(ConnectionState::Initial)
{
    connect(m_discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this, &BluetoothManager::deviceDiscovered);
    connect(m_discoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished, this,
            &BluetoothManager::discoveryFinished);
    connect(m_discoveryAgent, &QBluetoothDeviceDiscoveryAgent::errorOccurred,
            this, &BluetoothManager::discoveryError);

    createSocket();

    init();
}

void BluetoothManager::setConnectionState(ConnectionState state) {
    if (m_connectionState != state) {
        m_connectionState = state;
        emit connectionStateChanged();
    }
}

void BluetoothManager::init() {
    QString address = m_settingsManager->getLastDeviceAddress();
    QString name = m_settingsManager->getLastDeviceName();

    if (!address.isEmpty()) {
        qDebug() << "Restoring device:" << name << address;

        m_restoredAddress = QBluetoothAddress(address);
        m_attemptReconnect = true;

        startDiscovery();
    }
}

void BluetoothManager::startDiscovery() {
    if (m_discoveryAgent->isActive())
        return;

    QBluetoothPermission permission;
    permission.setCommunicationModes(QBluetoothPermission::Access);

    auto permissionStatus =
        QCoreApplication::instance()->checkPermission(permission);

    if (permissionStatus == Qt::PermissionStatus::Granted) {
        qDebug() << "Starting Bluetooth discovery...";
        m_discoveryAgent->start();
        setConnectionState(ConnectionState::Discovering);
    } else if (permissionStatus == Qt::PermissionStatus::Undetermined) {
        qDebug() << "Requesting Bluetooth permission...";
        requestBluetoothPermission();
    } else {
        qWarning() << "Bluetooth permission denied. Cannot start discovery.";
        setConnectionState(ConnectionState::NotPermitted);
    }
}

void BluetoothManager::stopDiscovery() {
    qDebug() << "Stopping Bluetooth discovery.";
    if (m_discoveryAgent->isActive())
        m_discoveryAgent->stop();

    if (m_socket->state() != QBluetoothSocket::SocketState::ConnectedState) {
        setConnectionState(ConnectionState::Initial);
    } else {
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

void BluetoothManager::discoveryFinished() {
    qDebug() << "Discovery Finished.";
    if (m_socket->state() != QBluetoothSocket::SocketState::ConnectedState) {
        setConnectionState(ConnectionState::Initial);
    } else {
        setConnectionState(ConnectionState::Connected);
    }
}

void BluetoothManager::discoveryError(
    QBluetoothDeviceDiscoveryAgent::Error error) {
    qWarning() << "Discovery error:" << error;
    setConnectionState(ConnectionState::Error);
}

void BluetoothManager::onConnected() {
    m_obdDevice = m_pendingObdDevice;
    emit activeDeviceNameChanged();

    qDebug() << "Connected to OBD Device!";
    setConnectionState(ConnectionState::Connected);
    stopDiscovery();

    m_settingsManager->setLastDeviceAddress(m_obdDevice.address().toString());
    m_settingsManager->setLastDeviceName(m_obdDevice.name());
}

bool BluetoothManager::sendMessage(const QString &message) {
    if (m_socket->state() == QBluetoothSocket::SocketState::ConnectedState) {
        QString formattedMessage = message + "\r";
        QByteArray data = formattedMessage.toUtf8();
        qint64 bytesWritten = m_socket->write(data);

        if (bytesWritten != data.size()) {
            qWarning() << "Failed to write message:" << formattedMessage;
            return false;
        }

        qDebug() << "Sent:" << formattedMessage;
        return true;
    } else {
        qDebug() << "Not connected!";
        return false;
    }
}

ConnectionState BluetoothManager::getConnectionState() const {
    return m_connectionState;
}

QString BluetoothManager::getActiveDeviceName() const {
    if (m_connectionState == ConnectionState::Connecting &&
        m_pendingObdDevice.isValid()) {
        return m_pendingObdDevice.name();
    }
    if (m_connectionState == ConnectionState::Connected &&
        m_obdDevice.isValid()) {
        return m_obdDevice.name();
    }
    return "";
}

void BluetoothManager::clearResults() { m_model->clear(); }

void BluetoothManager::connectToOBD(const QBluetoothDeviceInfo &device) {
    if (!device.isValid()) {
        qWarning() << "Invalid OBD Device!";
        return;
    }

    resetSocket();

    setConnectionState(ConnectionState::Connecting);
    m_pendingObdDevice = device;

    emit activeDeviceNameChanged();

    qDebug() << "Connecting to OBD Device at" << device.address().toString();
    m_socket->connectToService(
        device.address(),
        QBluetoothUuid(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB")));
}

void BluetoothManager::onReadyRead() {
    QByteArray data = m_socket->readAll();
    emit messageReceived(data);
}

void BluetoothManager::onErrorOccurred(QBluetoothSocket::SocketError error) {
    qDebug() << "Bluetooth Error:" << error;
    m_pendingObdDevice = QBluetoothDeviceInfo();
    setConnectionState(ConnectionState::Error);
    qDebug() << "Resetting Bluetooth socket after error";
    resetSocket();
}

void BluetoothManager::onDisconnected() {
    qDebug() << "OBD Device disconnected!";
    m_obdDevice = QBluetoothDeviceInfo();
    m_pendingObdDevice = QBluetoothDeviceInfo();
    resetSocket();
    if (m_dataProvider)
        m_dataProvider->reset();
    setConnectionState(ConnectionState::Disconnected);
}

void BluetoothManager::createSocket() {
    m_socket =
        std::make_unique<QBluetoothSocket>(QBluetoothServiceInfo::RfcommProtocol);

    connect(m_socket.get(), &QBluetoothSocket::connected, this,
            &BluetoothManager::onConnected);
    connect(m_socket.get(), &QBluetoothSocket::readyRead, this,
            &BluetoothManager::onReadyRead);
    connect(m_socket.get(), &QBluetoothSocket::errorOccurred, this,
            &BluetoothManager::onErrorOccurred);
    connect(m_socket.get(), &QBluetoothSocket::disconnected, this,
            &BluetoothManager::onDisconnected);
}

void BluetoothManager::resetSocket() {
    if (m_socket) {
        m_socket->disconnectFromService();
        m_socket->close();
    }

    createSocket();
}

void BluetoothManager::requestBluetoothPermission() {
    QBluetoothPermission permission;
    permission.setCommunicationModes(QBluetoothPermission::Access);

    qApp->requestPermission(permission, [this](const QPermission &perm) {
        if (perm.status() == Qt::PermissionStatus::Granted) {
            qDebug() << "Bluetooth permission granted.";
            startDiscovery();
        } else if (perm.status() == Qt::PermissionStatus::Denied) {
            qDebug() << "Bluetooth permission denied.";
            setConnectionState(ConnectionState::NotPermitted);
        } else {
            qDebug() << "Bluetooth permission status is unknown.";
            setConnectionState(ConnectionState::NotPermitted);
        }
    });
}
