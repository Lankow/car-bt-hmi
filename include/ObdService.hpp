#ifndef OBDSERVICE_HPP
#define OBDSERVICE_HPP
#include <QObject>
#include <QTimer>
#include "BluetoothManager.hpp"
#include "SettingsManager.hpp"
#include "DataProvider.hpp"

class ObdService : public QObject
{
    Q_OBJECT

public:
    ObdService(BluetoothManager* btManager, SettingsManager* settingsManagers, DataProvider* provider, QObject* parent = nullptr);

    void start(int intervalMs);
    void stop();

private slots:
    void handleBtStateChanged();
    void onMessageReceived(const QByteArray &message);
    void sendNextRequest();

private:
    qint64 parseResponse(const QByteArray &data, int startByte, int byteCount);

    BluetoothManager* m_btManager;
    SettingsManager* m_settingsManager;
    DataProvider* m_dataProvider;

    QTimer m_requestTimer;
    QStringList m_requests;
    int m_currentRequestIndex;
};

#endif // OBDSERVICE_HPP
