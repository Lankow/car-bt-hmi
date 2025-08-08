#ifndef BLUETOOTHMANAGER_HPP
#define BLUETOOTHMANAGER_HPP

#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothDeviceInfo>
#include <QBluetoothSocket>
#include <QObject>
#include <memory>
#include "ConnectionState.hpp"
#include "DeviceModel.hpp"
#include "SettingsManager.hpp"
#include "DataProvider.hpp"

using ConnectionState = ConnectionStateHelper::ConnectionState;

class BluetoothManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(ConnectionState connectionState READ getConnectionState NOTIFY
                   connectionStateChanged)
    Q_PROPERTY(QString activeDeviceName READ getActiveDeviceName NOTIFY
                   activeDeviceNameChanged)

public:
    explicit BluetoothManager(DeviceModel *model, SettingsManager *settingsManager, DataProvider *dataProvider, QObject *parent = nullptr);

    Q_INVOKABLE void startDiscovery();
    Q_INVOKABLE void stopDiscovery();
    Q_INVOKABLE void clearResults();
    Q_INVOKABLE void connectToOBD(const QBluetoothDeviceInfo &device);
    bool sendMessage(const QString &message);

    ConnectionState getConnectionState() const;
    QString getActiveDeviceName() const;

    void init();

signals:
    void deviceFound(const QString &deviceName);
    void connectionStateChanged();
    void activeDeviceNameChanged();
    void messageReceived(const QByteArray &data);

private slots:
    void deviceDiscovered(const QBluetoothDeviceInfo &device);
    void discoveryFinished();
    void discoveryError(QBluetoothDeviceDiscoveryAgent::Error error);
    void onConnected();
    void onReadyRead();
    void onDisconnected();
    void onErrorOccurred(QBluetoothSocket::SocketError error);

private:
    QBluetoothDeviceDiscoveryAgent *m_discoveryAgent;
    std::unique_ptr<QBluetoothSocket> m_socket;
    QBluetoothDeviceInfo m_pendingObdDevice;
    QBluetoothDeviceInfo m_obdDevice;
    ConnectionState m_connectionState;
    DeviceModel *m_model;
    SettingsManager *m_settingsManager;
    DataProvider *m_dataProvider;

    QBluetoothAddress m_restoredAddress;
    bool m_attemptReconnect = false;
    void setConnectionState(ConnectionState state);
    void createSocket();
    void resetSocket();
    void requestBluetoothPermission();
};

#endif // BLUETOOTHMANAGER_HPP
