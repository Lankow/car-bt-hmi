#include "DataProvider.hpp"

constexpr int DEFAULT_VEH_SPEED = 0;
constexpr int DEFAULT_ENG_SPEED = 0;

DataProvider::DataProvider(QObject *parent)
    : QObject(parent),
    m_vehicleSpeed(DEFAULT_VEH_SPEED),
    m_engineSpeed(DEFAULT_ENG_SPEED){}

int DataProvider::vehicleSpeed() const
{
    return m_vehicleSpeed;
}

int DataProvider::engineSpeed() const
{
    return m_engineSpeed;
}

void DataProvider::setVehicleSpeed(int speed)
{
    if (m_vehicleSpeed != speed) {
        m_vehicleSpeed = speed;
        emit vehicleSpeedChanged();
    }
}

void DataProvider::setEngineSpeed(int speed)
{
    if (m_engineSpeed != speed) {
        m_engineSpeed = speed;
        emit engineSpeedChanged();
    }
}
