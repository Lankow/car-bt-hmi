#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>s
#include "BluetoothManager.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    BluetoothManager btManager(nullptr);

    QQmlApplicationEngine engine;
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
