#ifndef SETTINGSMANAGER_HPP
#define SETTINGSMANAGER_HPP

#include <QObject>

class SettingsManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool loggingEnabled READ getLoggingEnabled WRITE setLoggingEnabled NOTIFY loggingEnabledChanged)
    Q_PROPERTY(QString lastDeviceAddress READ getLastDeviceAddress WRITE setLastDeviceAddress NOTIFY lastDeviceAddressChanged)
    Q_PROPERTY(QString lastDeviceName READ getLastDeviceName WRITE setLastDeviceName NOTIFY lastDeviceNameChanged)

public:
    enum SettingKey {
        LoggingEnabled,
    };
    Q_ENUM(SettingKey)

    explicit SettingsManager(QObject *parent = nullptr);

    Q_INVOKABLE void resetSettings();
    Q_INVOKABLE void toggleSetting(SettingsManager::SettingKey key);

    bool getLoggingEnabled() const;
    void setLoggingEnabled(bool enabled);

    QString getLastDeviceName() const;
    QString getLastDeviceAddress() const;

    void setLastDeviceName(const QString &deviceName);
    void setLastDeviceAddress(const QString &deviceAddress);

signals:
    void loggingEnabledChanged();
    void lastDeviceNameChanged();
    void lastDeviceAddressChanged();

private:
    bool m_loggingEnabled = false;
};


#endif // SETTINGSMANAGER_HPP
