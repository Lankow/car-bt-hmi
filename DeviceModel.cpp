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

    switch(role){
        case NameRole: return device.name;
        case AddressRole: return device.address;
        default: return {};
    }
    return QVariant();
}

QHash<int, QByteArray> DeviceModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[NameRole] = "name";
    names[AddressRole] = "address";
    return names;
}

void DeviceModel::addDevice(const DeviceInfo &device) {
    beginInsertRows(QModelIndex(), m_devices.count(), m_devices.count());
    m_devices.append(device);
    endInsertRows();
}

void DeviceModel::clear() {
    beginResetModel();
    m_devices.clear();
    endResetModel();
}
