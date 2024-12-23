#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "gauge.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    qmlRegisterType<Gauge>("com.voknal.gauge", 1, 0, "Gauge");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    QObject *object = engine.rootObjects()[0];
    QObject *speedGauge = object->findChild<QObject*>("speedGauge");

    Gauge *ptrSpeedGauge = dynamic_cast<Gauge*>(speedGauge);
    ptrSpeedGauge->setGaugeValue(120);

    return app.exec();
}
