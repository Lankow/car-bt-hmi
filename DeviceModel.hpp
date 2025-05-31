#ifndef DEVICEMODEL_HPP
#define DEVICEMODEL_HPP

#include <QAbstractListModel>
#include "DeviceInfo.hpp"

class DeviceModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit DeviceModel(QObject *parent = nullptr);

    enum {
        NameRole = Qt::UserRole,
        AddressRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void clear();
    void addDevice(const DeviceInfo &device);

private:
    QList<DeviceInfo> m_devices;
};

#endif // DEVICEMODEL_HPP
