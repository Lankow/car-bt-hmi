#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFontDatabase>
#include <QQmlContext>
#include "BluetoothManager.hpp"
#include "SettingsManager.hpp"
#include "DeviceModel.hpp"
#include "DataProvider.hpp"
#include "Gauge.hpp"
#include "StateIndicator.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Voknal");
    QCoreApplication::setApplicationName("CarBtHmi");

    QGuiApplication app(argc, argv);

    QFontDatabase::addApplicationFont(":/Orbitron.ttf");
    qmlRegisterType<Gauge>("CustomControls", 1, 0, "Gauge");
    qmlRegisterType<StateIndicator>("CustomControls", 1, 0, "StateIndicator");

    DataProvider dataProvider;
    DeviceModel deviceModel;
    SettingsManager settingsManager;
    BluetoothManager btManager(&deviceModel);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("settingsManager", &settingsManager);
    engine.rootContext()->setContextProperty("dataProvider", &dataProvider);
    engine.rootContext()->setContextProperty("bluetoothManager", &btManager);
    engine.rootContext()->setContextProperty("deviceModel", &deviceModel);

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
