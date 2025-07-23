#include "ObdService.hpp"

ObdService::ObdService(BluetoothManager* btManager, DataProvider* provider, QObject* parent)
    : QObject(parent), m_btManager(btManager), m_dataProvider(provider), m_currentRequestIndex(0)
{
    connect(btManager, &BluetoothManager::messageReceived, this, &ObdService::onMessageReceived);
    connect(btManager, &BluetoothManager::connectionStateChanged, this, &ObdService::handleBtStateChanged);

    m_requests << "010D"  // Vehicle Speed
               << "010C"; // Engine RPM

    connect(&m_requestTimer, &QTimer::timeout, this, &ObdService::sendNextRequest);
}

void ObdService::start(int intervalMs)
{
    m_requestTimer.setInterval(intervalMs);
    m_requestTimer.start();
}

void ObdService::stop()
{
    m_requestTimer.stop();
}

void ObdService::sendNextRequest()
{
    QString command = m_requests[m_currentRequestIndex];
    if (m_btManager->sendMessage(command))
    {
        m_currentRequestIndex = (m_currentRequestIndex + 1) % m_requests.size();
    }
}

void ObdService::onMessageReceived(const QString& message)
{
    qDebug() << "Received Message:" << message;
}

void ObdService::handleBtStateChanged()
{
    if (m_btManager->getConnectionState() == ConnectionState::Connected)
    {
        start(100);
        qDebug() << "Started requests transmission.";
    }
    else
    {
        stop();
        qDebug() << "Stopped requests transmission.";
    }
}
