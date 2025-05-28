#ifndef DEVICEMODEL_HPP
#define DEVICEMODEL_HPP

#include <QAbstractListModel>
#include "deviceinfo.hpp"

class DeviceModel : public QAbstractListModel {
    Q_OBJECT

public:
    enum DeviceRoles {
        NameRole = Qt::UserRole + 1,
        AddressRole
    };

    explicit DeviceModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void clear();
    void addDevice(const DeviceInfo &device);

private:
    QList<DeviceInfo> m_devices;
};

#endif // DEVICEMODEL_HPP
