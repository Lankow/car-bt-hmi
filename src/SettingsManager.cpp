#include "SettingsManager.hpp"
#include <QSettings>
#include <QDebug>

namespace {
const QString KEY_LAST_DEVICE_ADDRESS = QStringLiteral("lastDeviceAddress");
const QString KEY_LAST_DEVICE_NAME = QStringLiteral("lastDeviceName");
const QString KEY_LOGGING_ENABLED = QStringLiteral("loggingEnabled");
const QString KEY_CLOCK_ENABLED = QStringLiteral("clockEnabled");
const QString KEY_CYCLE_INTERVAL_MS = QStringLiteral("cycleIntervalMs");

const int DEFAULT_CYCLE_INTERVAL_MS = 100;
const int MIN_CYCLE_INTERVAL_MS = 50;
const int MAX_CYCLE_INTERVAL_MS = 1000;
}



SettingsManager::SettingsManager(QObject *parent)
    : QObject(parent) {}

void SettingsManager::resetSettings() {
    setLastDeviceName("");
    setLastDeviceAddress("");
    setLoggingEnabled(false);
    setClockEnabled(true);
    setCycleIntervalMs(DEFAULT_CYCLE_INTERVAL_MS);
}

bool SettingsManager::getLoggingEnabled() const {
    QSettings settings;
    return settings.value(KEY_LOGGING_ENABLED, false).toBool();
}

void SettingsManager::setLoggingEnabled(bool enabled) {
    QSettings settings;
    if (settings.value(KEY_LOGGING_ENABLED, false).toBool() == enabled)
        return;

    settings.setValue(KEY_LOGGING_ENABLED, enabled);
    emit loggingEnabledChanged();
}

bool SettingsManager::getClockEnabled() const {
    QSettings settings;
    return settings.value(KEY_CLOCK_ENABLED, true).toBool();
}

void SettingsManager::setClockEnabled(bool enabled) {
    QSettings settings;
    if (settings.value(KEY_CLOCK_ENABLED, false).toBool() == enabled)
        return;

    settings.setValue(KEY_CLOCK_ENABLED, enabled);
    emit clockEnabledChanged();
}

QString SettingsManager::getLastDeviceName() const {
    QSettings settings;
    return settings.value(KEY_LAST_DEVICE_NAME, "").toString();
}

QString SettingsManager::getLastDeviceAddress() const {
    QSettings settings;
    return settings.value(KEY_LAST_DEVICE_ADDRESS, "").toString();
}

void SettingsManager::setLastDeviceName(const QString &name) {
    QSettings settings;
    settings.setValue(KEY_LAST_DEVICE_NAME, name);
    emit lastDeviceNameChanged();
}

void SettingsManager::setLastDeviceAddress(const QString &address) {
    QSettings settings;
    settings.setValue(KEY_LAST_DEVICE_ADDRESS, address);
    emit lastDeviceAddressChanged();
}

int SettingsManager::getCycleIntervalMs() const {
    QSettings settings;
    return settings.value(KEY_CYCLE_INTERVAL_MS, DEFAULT_CYCLE_INTERVAL_MS).toInt();
}

void SettingsManager::setCycleIntervalMs(int intervalMs) {
    QSettings settings;
    if (intervalMs > MAX_CYCLE_INTERVAL_MS ||
        intervalMs < MIN_CYCLE_INTERVAL_MS ||
        settings.value(KEY_CYCLE_INTERVAL_MS, DEFAULT_CYCLE_INTERVAL_MS).toInt() == intervalMs)
        return;

    settings.setValue(KEY_CYCLE_INTERVAL_MS, intervalMs);
    emit cycleIntervalMsChanged();
}

void SettingsManager::toggleSetting(SettingsManager::SettingKey key) {
    QSettings settings;
    switch (key) {
    case LoggingEnabled:
        setLoggingEnabled(!getLoggingEnabled());
        break;
    case ClockEnabled:
        setClockEnabled(!getClockEnabled());
        break;
    default:
        qWarning("toggleSetting: Unsupported key");
    }
}
