#include "DataProvider.hpp"

constexpr int DEFAULT_VEH_SPEED = 0;
constexpr int DEFAULT_ENG_SPEED = 0;

DataProvider::DataProvider():
    m_vehicleSpeed(DEFAULT_VEH_SPEED),
    m_engineSpeed(DEFAULT_ENG_SPEED) {};

