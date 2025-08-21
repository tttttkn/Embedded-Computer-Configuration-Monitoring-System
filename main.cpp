#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "Model/cpumodel.h"
#include "Model/memorymodel.h"
#include "Model/networkmodel.h"
#include "Model/storagemodel.h"
#include "Model/gpumodel.h"
#include "Model/systemmodel.h"
#include "Controllers/navigationcontroller.h"
#include "Controllers/modelcontroller.h"
#include "Controllers/logger.h"
#include "Controllers/alert.h"
#include "QDateTime"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

//    QGuiApplication app(argc, argv);
    QApplication app(argc, argv);
    qRegisterMetaType<CpuInfo>("CpuInfo");
    qRegisterMetaType<GpuInfo>("GpuInfo");
    qRegisterMetaType<MemoryInfo>("MemoryInfo");
    qRegisterMetaType<NetworkInfo>("NetworkInfo");
    qRegisterMetaType<StorageInfo>("StorageInfo");
    qRegisterMetaType<StaticSystemInfo>("StaticSystemInfo");

    QQmlApplicationEngine engine;
    ModelController modelController;
    NavigationController navigator;

    engine.rootContext()->setContextProperty("navigator", &navigator);
    engine.rootContext()->setContextProperty("modelController", &modelController);
    engine.rootContext()->setContextProperty("logger", Logger::getInstance());
    engine.rootContext()->setContextProperty("alertModel", Alert::getInstance());




    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    modelController.initModel();
    modelController.initServices();
    
    engine.load(url);
    
    Logger::addLog("System monitoring started");


    return app.exec();
}
