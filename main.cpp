#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "bluetoothmanager.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // Register BluetoothManager as a QML type
    qmlRegisterType<BluetoothManager>("com.app.bluetooth", 1, 0, "BluetoothManager");

    const QUrl url(QStringLiteral("qrc:/car-bt-hmi/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
