#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFontDatabase>
#include <QQmlContext>
#include "BluetoothManager.hpp"
#include "DeviceModel.hpp"
#include "Gauge.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    int id = QFontDatabase::addApplicationFont(":/Orbitron.ttf");
    if (id == -1) {
        qWarning() << "Failed to load Orbitron font.";
    } else {
        QStringList loadedFamilies = QFontDatabase::applicationFontFamilies(id);
        if (!loadedFamilies.isEmpty()) {
            qDebug() << "Font loaded successfully:" << loadedFamilies.first();
        }
    }

    qmlRegisterType<Gauge>("com.voknal.gauge", 1, 0, "Gauge");

    DeviceModel deviceModel;
    BluetoothManager btManager(&deviceModel);

    QQmlApplicationEngine engine;
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
