#include "SettingsManager.hpp"
#include <QSettings>
#include <QDebug>

namespace {
const QString KEY_SETTINGS_INITIALIZED = QStringLiteral("settingsInitialized");
const QString KEY_LAST_DEVICE_ADDRESS = QStringLiteral("lastDeviceAddress");
const QString KEY_LAST_DEVICE_NAME = QStringLiteral("lastDeviceName");
const QString KEY_LOGGING_ENABLED = QStringLiteral("loggingEnabled");
const QString KEY_CLOCK_ENABLED = QStringLiteral("clockEnabled");
const QString KEY_CYCLE_INTERVAL_MS = QStringLiteral("cycleIntervalMs");
const QString KEY_OBD_PID_LIST = QStringLiteral("obdPidList");

const int DEFAULT_CYCLE_INTERVAL_MS = 100;
const int MIN_CYCLE_INTERVAL_MS = 50;
const int MAX_CYCLE_INTERVAL_MS = 1000;
}

SettingsManager::SettingsManager(QObject *parent)
    : QObject(parent) {
    QSettings settings;
    if (!settings.value(KEY_SETTINGS_INITIALIZED, false).toBool()) {
        resetSettings();
        settings.setValue(KEY_SETTINGS_INITIALIZED, true);
    }
}

void SettingsManager::resetSettings() {
    QSettings settings;
    settings.setValue(KEY_OBD_PID_LIST, QStringList());

    setLastDeviceName("");
    setLastDeviceAddress("");
    setLoggingEnabled(false);
    setClockEnabled(true);
    setCycleIntervalMs(DEFAULT_CYCLE_INTERVAL_MS);

    addObdPid("010D"); // Vehicle Speed
    addObdPid("010C"); // Engine RPM
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

QStringList SettingsManager::getObdPidList() const {
    QSettings settings;
    return settings.value(KEY_OBD_PID_LIST, QStringList()).toStringList();
}

void SettingsManager::toggleSetting(SettingsManager::SettingKey key) {
    switch (key) {
    case LoggingEnabled:
        setLoggingEnabled(!getLoggingEnabled());
        break;
    case ClockEnabled:
        setClockEnabled(!getClockEnabled());
        break;
    case VehicleSpeedEnabled: {
        QString pid = "010D";
        if (hasObdPid(pid))
            removeObdPid(pid);
        else
            addObdPid(pid);
        emit vehicleSpeedEnabledChanged();
        break;
    }
    case EngineSpeedEnabled: {
        QString pid = "010C";
        if (hasObdPid(pid))
            removeObdPid(pid);
        else
            addObdPid(pid);
        emit engineSpeedEnabledChanged();
        break;
    }
    default:
        qWarning("toggleSetting: Unsupported key");
    }
}

void SettingsManager::addObdPid(const QString &pid) {
    QSettings settings;
    QStringList list = settings.value(KEY_OBD_PID_LIST, QStringList()).toStringList();

    if (!list.contains(pid)) {
        list.append(pid);
        settings.setValue(KEY_OBD_PID_LIST, list);
        emit obdPidListChanged();
    }
}

void SettingsManager::removeObdPid(const QString &pid) {
    QSettings settings;
    QStringList list = settings.value(KEY_OBD_PID_LIST, QStringList()).toStringList();

    if (list.removeAll(pid) > 0) {
        settings.setValue(KEY_OBD_PID_LIST, list);
        emit obdPidListChanged();
    }
}

bool SettingsManager::hasObdPid(const QString &pid) const {
    return getObdPidList().contains(pid);
}

bool SettingsManager::getVehicleSpeedEnabled() const {
    return hasObdPid("010D");
}

void SettingsManager::setVehicleSpeedEnabled(bool enabled) {
    if (enabled && !hasObdPid("010D")) {
        addObdPid("010D");
        emit vehicleSpeedEnabledChanged();
    } else if (!enabled && hasObdPid("010D")) {
        removeObdPid("010D");
        emit vehicleSpeedEnabledChanged();
    }
}

bool SettingsManager::getEngineSpeedEnabled() const {
    return hasObdPid("010C");
}

void SettingsManager::setEngineSpeedEnabled(bool enabled) {
    if (enabled && !hasObdPid("010C")) {
        addObdPid("010C");
        emit engineSpeedEnabledChanged();
    } else if (!enabled && hasObdPid("010C")) {
        removeObdPid("010C");
        emit engineSpeedEnabledChanged();
    }
}
