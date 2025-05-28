#ifndef DEVICEINFO_HPP
#define DEVICEINFO_HPP

#include <QString>
#include <QBluetoothDeviceInfo>
#include <QBluetoothAddress>

struct DeviceInfo {
    QString name;
    QString address;

    DeviceInfo() = default;
    DeviceInfo(const QBluetoothDeviceInfo &info)
        : name(info.name()), address(info.address().toString()) {}
};

#endif // DEVICEINFO_HPP
