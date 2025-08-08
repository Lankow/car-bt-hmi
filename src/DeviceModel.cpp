#include "DeviceModel.hpp"

DeviceModel::DeviceModel(QObject *parent)
    : QAbstractListModel(parent)
{}

int DeviceModel::rowCount(const QModelIndex &) const {
    return m_devices.count();
}

QVariant DeviceModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_devices.size())
        return {};

    const auto &device = m_devices[index.row()];

    switch (role) {
    case NameRole:
        return device.name();
    case AddressRole:
        return device.address().toString();
    case DeviceRole:
        return QVariant::fromValue(device);
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> DeviceModel::roleNames() const
{
    static const QHash<int, QByteArray> names{
                                              {NameRole, "name"},
                                              {AddressRole, "address"},
                                              {DeviceRole, "device"},
                                              };
    return names;
}

void DeviceModel::addDevice(const QBluetoothDeviceInfo &device) {

    for (const QBluetoothDeviceInfo &d : std::as_const(m_devices)) {
        if (d.address() == device.address())
            return;
    }

    beginInsertRows(QModelIndex(), m_devices.size(), m_devices.size());
    m_devices.append(device);
    endInsertRows();
}

void DeviceModel::clear() {
    beginResetModel();
    m_devices.clear();
    endResetModel();
}
