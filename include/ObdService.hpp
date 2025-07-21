#ifndef OBDSERVICE_HPP
#define OBDSERVICE_HPP
#include <QObject>
#include <QTimer>
#include "BluetoothManager.hpp"
#include "DataProvider.hpp"

class ObdService : public QObject
{
    Q_OBJECT

public:
    ObdService(BluetoothManager* btManager, DataProvider* provider, QObject* parent = nullptr);

    void start();
    void stop();

private slots:
    void onMessageReceived(const QString& message);
    void writeNextRequest();

private:
    BluetoothManager* m_btManager;
    DataProvider* m_dataProvider;

    QTimer m_requestTimer;
    QStringList m_requests;
    int m_currentRequestIndex;
};

#endif // OBDSERVICE_HPP
