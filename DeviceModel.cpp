#include "DeviceModel.hpp"

DeviceModel::DeviceModel(QObject *parent)
    : QAbstractListModel(parent)
{}

int DeviceModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 10;
}


QVariant DeviceModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch(role){
    case NameRole:
        return QStringLiteral("Name");
    case AddressRole:
        return QStringLiteral("Address");
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
