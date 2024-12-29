#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFontDatabase>
#include <QTimer>
#include "gauge.h"
#include "obdhandler.h"

//#define DEMO_MODE

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
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
    QObject *rpmGauge = object->findChild<QObject*>("rpmGauge");

    Gauge *ptrSpeedGauge = dynamic_cast<Gauge*>(speedGauge);
    Gauge *ptrRpmGauge = dynamic_cast<Gauge*>(rpmGauge);

    ptrSpeedGauge->setValue(0);
    ptrRpmGauge->setValue(0);

#ifndef DEMO_MODE
    ObdHandler obdHandler;
    obdHandler.init();

    QObject::connect(&obdHandler, &ObdHandler::speedUpdated, ptrSpeedGauge, &Gauge::setValue);
    QObject::connect(&obdHandler, &ObdHandler::rpmUpdated, ptrRpmGauge, &Gauge::setValue);
#else
    bool speedDirection = true; // true: increasing, false: decreasing
    bool rpmDirection = true;   // true: increasing, false: decreasing
#endif

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]()
                     {
#ifndef DEMO_MODE
                         obdHandler.getSpeed();
                         QTimer::singleShot(100, [&]()
                                            {
                                                obdHandler.getRPM();
                                            });
#else
            int speedValue = ptrSpeedGauge->getValue();
            if (speedDirection) {
                if (speedValue < ptrSpeedGauge->getMaxValue()) {
                    ptrSpeedGauge->setValue(speedValue + 1);
                } else {
                    speedDirection = false;
                }
            } else {
                if (speedValue > ptrSpeedGauge->getMinValue()) {
                    ptrSpeedGauge->setValue(speedValue - 1);
                } else {
                    speedDirection = true;
                }
            }

            int rpmValue = ptrRpmGauge->getValue();
            if (rpmDirection) {
                if (rpmValue < ptrRpmGauge->getMaxValue()) {
                    ptrRpmGauge->setValue(rpmValue + 100);
                } else {
                    rpmDirection = false;
                }
            } else {
                if (rpmValue > ptrRpmGauge->getMinValue()) {
                    ptrRpmGauge->setValue(rpmValue - 100);
                } else {
                    rpmDirection = true;
                }
            }
#endif
                     });
#ifndef DEMO_MODE
    timer.start(200);
#else
    timer.start(40);
#endif
    return app.exec();
}
