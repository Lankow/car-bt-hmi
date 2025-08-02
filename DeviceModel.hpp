#ifndef DEVICEMODEL_HPP
#define DEVICEMODEL_HPP

#include <QAbstractListModel>
#include <QBluetoothDeviceInfo>
#include <QBluetoothSocket>

class DeviceModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit DeviceModel(QObject *parent = nullptr);

    enum DeviceRoles {
        NameRole = Qt::UserRole,
        AddressRole,
        DeviceRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void clear();
    void addDevice(const QBluetoothDeviceInfo &device);

private:
    QList<QBluetoothDeviceInfo> m_devices;
};

#endif // DEVICEMODEL_HPP
