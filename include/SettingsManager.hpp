#ifndef SETTINGSMANAGER_HPP
#define SETTINGSMANAGER_HPP

#include <QObject>
#include <QSettings>

class SettingsManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool loggingEnabled READ getLoggingEnabled WRITE setLoggingEnabled NOTIFY loggingEnabledChanged)
    Q_PROPERTY(bool clockEnabled READ getClockEnabled WRITE setClockEnabled NOTIFY clockEnabledChanged)
    Q_PROPERTY(QString lastDeviceAddress READ getLastDeviceAddress WRITE setLastDeviceAddress NOTIFY lastDeviceAddressChanged)
    Q_PROPERTY(QString lastDeviceName READ getLastDeviceName WRITE setLastDeviceName NOTIFY lastDeviceNameChanged)
    Q_PROPERTY(int cycleIntervalMs READ getCycleIntervalMs WRITE setCycleIntervalMs NOTIFY cycleIntervalMsChanged)
    Q_PROPERTY(bool vehicleSpeedEnabled READ getVehicleSpeedEnabled WRITE setVehicleSpeedEnabled NOTIFY vehicleSpeedEnabledChanged)
    Q_PROPERTY(bool engineSpeedEnabled READ getEngineSpeedEnabled WRITE setEngineSpeedEnabled NOTIFY engineSpeedEnabledChanged)
    Q_PROPERTY(QStringList obdPidList READ getObdPidList NOTIFY obdPidListChanged)

public:
    enum SettingKey {
        LoggingEnabled,
        ClockEnabled,
        VehicleSpeedEnabled,
        EngineSpeedEnabled,
        CycleIntervalMs
    };
    Q_ENUM(SettingKey)

    explicit SettingsManager(QObject *parent = nullptr);

    Q_INVOKABLE void resetSettings();
    Q_INVOKABLE void toggleSetting(SettingsManager::SettingKey key);
    Q_INVOKABLE void addObdPid(const QString &pid);
    Q_INVOKABLE void removeObdPid(const QString &pid);
    Q_INVOKABLE bool hasObdPid(const QString &pid) const;

    bool getLoggingEnabled() const;
    void setLoggingEnabled(bool enabled);

    bool getClockEnabled() const;
    void setClockEnabled(bool enabled);

    QString getLastDeviceName() const;
    QString getLastDeviceAddress() const;

    int getCycleIntervalMs() const;
    void setCycleIntervalMs(int intervalMs);

    void setLastDeviceName(const QString &deviceName);
    void setLastDeviceAddress(const QString &deviceAddress);

    bool getVehicleSpeedEnabled() const;
    void setVehicleSpeedEnabled(bool enabled);

    bool getEngineSpeedEnabled() const;
    void setEngineSpeedEnabled(bool enabled);

    QStringList getObdPidList() const;

signals:
    void loggingEnabledChanged();
    void clockEnabledChanged();
    void lastDeviceNameChanged();
    void lastDeviceAddressChanged();
    void cycleIntervalMsChanged();
    void vehicleSpeedEnabledChanged();
    void engineSpeedEnabledChanged();
    void obdPidListChanged();

private:
    QSettings m_settings;
};

#endif // SETTINGSMANAGER_HPP
