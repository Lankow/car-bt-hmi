#ifndef SETTINGSMANAGER_HPP
#define SETTINGSMANAGER_HPP

#include <QObject>

class SettingsManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool loggingEnabled READ getLoggingEnabled WRITE setLoggingEnabled NOTIFY loggingEnabledChanged)

public:
    enum SettingKey {
        LoggingEnabled,
    };
    Q_ENUM(SettingKey)

    explicit SettingsManager(QObject *parent = nullptr);

    Q_INVOKABLE void clearSettings();
    Q_INVOKABLE bool getLoggingEnabled() const;
    Q_INVOKABLE void setLoggingEnabled(bool enabled);
    Q_INVOKABLE void toggleSetting(SettingsManager::SettingKey key);

signals:
    void loggingEnabledChanged();

private:
    bool m_loggingEnabled = false;
};


#endif // SETTINGSMANAGER_HPP
