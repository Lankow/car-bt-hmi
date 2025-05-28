#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>s
#include "bluetoothmanager.hpp"
#include "devicemodel.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    DeviceModel deviceModel;
    BluetoothManager btManager(&deviceModel);  // inject model

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("deviceModel", &deviceModel);
    engine.rootContext()->setContextProperty("bluetoothManager", &btManager);

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
