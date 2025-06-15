#include "SettingsManager.hpp"
#include <QDebug>
#include <QSettings>

SettingsManager::SettingsManager(QObject *parent)
    : QObject(parent){}

void SettingsManager::clearSettings() {
    QSettings settings;
    settings.clear();
}
