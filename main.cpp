#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "Model/cpumodel.h"
#include "Model/memorymodel.h"
#include "Model/networkmodel.h"
#include "Model/storagemodel.h"
#include "Model/gpumodel.h"
#include "Controllers/navigationcontroller.h"
#include "Controllers/modelcontroller.h"

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

    QQmlApplicationEngine engine;
    ModelController modelController;
    NavigationController navigator;

    modelController.initServices();
    engine.rootContext()->setContextProperty("navigator", &navigator);
    engine.rootContext()->setContextProperty("modelController", &modelController);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
