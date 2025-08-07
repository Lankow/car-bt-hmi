#include "ObdService.hpp"

ObdService::ObdService(BluetoothManager* btManager, SettingsManager* settingsManager, DataProvider* provider, QObject* parent)
    : QObject(parent), m_btManager(btManager), m_settingsManager(settingsManager), m_dataProvider(provider), m_currentRequestIndex(0)
{
    connect(btManager, &BluetoothManager::messageReceived, this, &ObdService::onMessageReceived);
    connect(btManager, &BluetoothManager::connectionStateChanged, this, &ObdService::handleBtStateChanged);
    connect(settingsManager, &SettingsManager::cycleIntervalMsChanged, this, &ObdService::handleIntervalChanged);
    connect(settingsManager, &SettingsManager::obdPidListChanged, this, &ObdService::handleObdPidListChanged);

    m_requests = settingsManager->getObdPidList();
    connect(&m_requestTimer, &QTimer::timeout, this, &ObdService::sendNextRequest);
}

void ObdService::start(int intervalMs)
{
    if(m_requests.isEmpty()) return;
    int divisionResult = intervalMs / m_requests.count();
    if(divisionResult < 1)
    {
        qWarning() << "Request interval less than 1ms, clamping to 1ms.";
    }

    int requestIntervalMs = qMax(1, divisionResult);
    m_requestTimer.setInterval(requestIntervalMs);
    m_requestTimer.start();
}

void ObdService::stop()
{
    m_requestTimer.stop();
}

void ObdService::sendNextRequest()
{
    if(m_requests.isEmpty()) return;

    QString command = m_requests[m_currentRequestIndex];
    if (m_btManager->sendMessage(command))
    {
        m_currentRequestIndex = (m_currentRequestIndex + 1) % m_requests.size();
    }
}

void ObdService::onMessageReceived(const QByteArray &message)
{
    QByteArray normalized = message.trimmed().toUpper();
    qDebug() << "Received Message:" << normalized;

    if (normalized.startsWith("41 0D")) {
        qint64 speed = parseResponse(normalized, 6, 2);
        if (speed != -1) {
            qDebug() << "Speed: " << speed;
            m_dataProvider->setVehicleSpeed(speed);
        }
    }

    if (normalized.startsWith("41 0C")) {
        qint64 rawRPM = parseResponse(normalized, 6, 5);
        if (rawRPM != -1) {
            qint64 rpm = rawRPM / 4;
            qDebug() << "RPM: " << rpm;
            m_dataProvider->setEngineSpeed(rpm);
        }
    }
}

void ObdService::handleBtStateChanged()
{
    if (m_btManager->getConnectionState() == ConnectionState::Connected)
    {
        start(m_settingsManager->getCycleIntervalMs());
        qDebug() << "Started requests transmission.";
    }
    else if (m_btManager->getConnectionState() != ConnectionState::Discovering)
    {
        stop();
        qDebug() << "Stopped requests transmission.";
    }
}

void ObdService::handleIntervalChanged()
{
    if (m_btManager->getConnectionState() == ConnectionState::Connected)
    {
        stop();
        start(m_settingsManager->getCycleIntervalMs());
        qDebug() << "Started requests transmission with updated Interval.";
    }
}

void ObdService::handleObdPidListChanged()
{
    stop();
    m_requests = m_settingsManager->getObdPidList();
    m_currentRequestIndex = 0;
    if(m_requests.isEmpty())
    {
        stop();
        return;
    }
    start(m_settingsManager->getCycleIntervalMs());
    qDebug() << "Started requests transmission with updated OBD PIDs.";
}

qint64 ObdService::parseResponse(const QByteArray &data, int startByte, int byteCount) {
    if (data.size() < startByte + byteCount) {
        qWarning() << "Invalid data length for parsing!";
        return -1;
    }

    QByteArray hexValue = data.mid(startByte, byteCount);
    hexValue.replace(" ", "");

    bool ok = false;
    uint value = hexValue.toUInt(&ok, 16);
    if (!ok) {
        qWarning() << "Failed to convert" << hexValue;
        return -1;
    }
    return value;
}
