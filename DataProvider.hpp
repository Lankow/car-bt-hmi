#ifndef DATAPROVIDER_HPP
#define DATAPROVIDER_HPP

#include <QObject>

class DataProvider : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int vehicleSpeed READ vehicleSpeed WRITE setVehicleSpeed NOTIFY vehicleSpeedChanged)
    Q_PROPERTY(int engineSpeed READ engineSpeed WRITE setEngineSpeed NOTIFY engineSpeedChanged)

public:
    explicit DataProvider(QObject *parent = nullptr);

    int vehicleSpeed() const;
    int engineSpeed() const;

    void setVehicleSpeed(int speed);
    void setEngineSpeed(int speed);

signals:
    void vehicleSpeedChanged();
    void engineSpeedChanged();

private:
    int m_vehicleSpeed;
    int m_engineSpeed;
};

#endif // DATAPROVIDER_HPP
