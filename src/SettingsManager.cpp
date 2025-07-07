#include "SettingsManager.hpp"
#include <QDebug>
#include <QSettings>
#include <QDebug>

SettingsManager::SettingsManager(QObject *parent)
    : QObject(parent){}

void SettingsManager::clearSettings() {
    QSettings settings;
    settings.clear();
}

bool SettingsManager::getLoggingEnabled() const
{
    return m_loggingEnabled;
}

void SettingsManager::setLoggingEnabled(bool enabled)
{
    if (m_loggingEnabled == enabled)
        return;

    m_loggingEnabled = enabled;
    emit loggingEnabledChanged();

    qDebug() << m_loggingEnabled;
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
