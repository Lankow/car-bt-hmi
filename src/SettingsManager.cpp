#include "SettingsManager.hpp"
#include <QDebug>
#include <QSettings>
#include <QDebug>

namespace {
const QString KEY_LAST_DEVICE_ADDRESS = QStringLiteral("lastDeviceAddress");
const QString KEY_LAST_DEVICE_NAME = QStringLiteral("lastDeviceName");
const QString KEY_LOGGING_ENABLED = QStringLiteral("loggingEnabled");
}

SettingsManager::SettingsManager(QObject *parent)
    : QObject(parent){}

void SettingsManager::resetSettings() {
    setLastDeviceName("");
    setLastDeviceAddress("");
}

bool SettingsManager::getLoggingEnabled() const
{
    return m_loggingEnabled;
}

QString SettingsManager::getLastDeviceName() const
{
    QSettings settings;
    return settings.value(KEY_LAST_DEVICE_NAME, "").toString();
}

QString SettingsManager::getLastDeviceAddress() const
{
    QSettings settings;
    return settings.value(KEY_LAST_DEVICE_ADDRESS, "").toString();
}

void SettingsManager::setLoggingEnabled(bool enabled)
{
    if (m_loggingEnabled == enabled)
        return;

    m_loggingEnabled = enabled;
    emit loggingEnabledChanged();
}

void SettingsManager::setLastDeviceName(const QString &name)
{
    QSettings settings;
    settings.setValue(KEY_LAST_DEVICE_NAME, name);
    emit lastDeviceNameChanged();
}

void SettingsManager::setLastDeviceAddress(const QString &address)
{
    QSettings settings;
    settings.setValue(KEY_LAST_DEVICE_ADDRESS, address);
    emit lastDeviceAddressChanged();
}

void SettingsManager::toggleSetting(SettingsManager::SettingKey key)
{
    switch (key) {
    case LoggingEnabled:
        setLoggingEnabled(!m_loggingEnabled);
        break;
    default:
        qWarning("toggleSetting: Unsupported key");
    }
}
