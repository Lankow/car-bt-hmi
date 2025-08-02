#ifndef CONNECTIONSTATE_HPP
#define CONNECTIONSTATE_HPP
#include <QObject>

class ConnectionStateHelper : public QObject {
    Q_GADGET

public:
    enum ConnectionState {
        Initial = 0,
        Discovering,
        Connecting,
        Connected,
        Disconnected,
        Error
    };
    Q_ENUM(ConnectionState)
};
#endif // CONNECTIONSTATE_HPP
