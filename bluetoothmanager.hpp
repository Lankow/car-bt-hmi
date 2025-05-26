#include <QObject>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothSocket>
#include <QBluetoothDeviceInfo>

#ifndef BLUETOOTHMANAGER_HPP
#define BLUETOOTHMANAGER_HPP

class BluetoothManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool connected READ isConnected NOTIFY connectedChanged)

public:
    explicit BluetoothManager(QObject *parent = nullptr);
    Q_INVOKABLE void startDiscovery();
    Q_INVOKABLE void stopDiscovery();
    Q_INVOKABLE void sendMessage(const QString &message);
    Q_INVOKABLE void connectToOBD();

    bool isConnected() const { return m_connected; }

signals:
    void deviceFound(const QString &deviceName);
    void connectedChanged();
    void messageReceived(const QString &message);

private slots:
    void deviceDiscovered(const QBluetoothDeviceInfo &device);
    void discoveryFinished();
    void onConnected();
    void onReadyRead();
    void onErrorOccurred(QBluetoothSocket::SocketError error);

private:
    QBluetoothDeviceDiscoveryAgent *m_discoveryAgent;
    QBluetoothSocket *m_socket;
    bool m_connected = false;
    QBluetoothDeviceInfo m_obdDevice;
};


#endif // BLUETOOTHMANAGER_HPP
