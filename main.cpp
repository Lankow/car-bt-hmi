#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFontDatabase>
#include <QQmlContext>
#include "BluetoothManager.hpp"
#include "SettingsManager.hpp"
#include "DeviceModel.hpp"
#include "DataProvider.hpp"
#include "ObdService.hpp"
#include "Gauge.hpp"
#include "StateIndicator.hpp"
#include "ConnectionState.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("LNKV");
    QCoreApplication::setApplicationName("CarBtHmi");

    QGuiApplication app(argc, argv);

    int fontId = QFontDatabase::addApplicationFont(":/fonts/Orbitron.ttf");
    if (fontId == -1)
        qWarning() << "Failed to load Orbitron font";

    qmlRegisterType<Gauge>("CustomControls", 1, 0, "Gauge");
    qmlRegisterType<StateIndicator>("CustomControls", 1, 0, "StateIndicator");
    qmlRegisterSingletonType(QUrl("qrc:/car-bt-hmi/qml/MenuState.qml"), "MenuState", 1, 0, "MenuState");
    qmlRegisterUncreatableType<SettingsManager>("Settings", 1, 0, "SettingsManager", "Enum access only");
    qmlRegisterUncreatableType<ConnectionStateHelper>("ConnectionState", 1, 0, "ConnectionState", "Enum only");

    DataProvider dataProvider;
    DeviceModel deviceModel;
    SettingsManager settingsManager;
    BluetoothManager btManager(&deviceModel, &settingsManager);
    ObdService obdService(&btManager, &settingsManager, &dataProvider);

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("settingsManager", &settingsManager);
    engine.rootContext()->setContextProperty("dataProvider", &dataProvider);
    engine.rootContext()->setContextProperty("bluetoothManager", &btManager);
    engine.rootContext()->setContextProperty("deviceModel", &deviceModel);

    QString appVersion = QStringLiteral(APP_VERSION);
    engine.rootContext()->setContextProperty("appVersion", appVersion);

    const QUrl url(QStringLiteral("qrc:/car-bt-hmi/qml/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
