#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "Model/cpumodel.h"
#include "Model/memorymodel.h"
#include "Model/networkmodel.h"
#include "Model/storagemodel.h"
#include "Model/gpumodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

//    QGuiApplication app(argc, argv);
    QApplication app(argc, argv);
    CpuModel cpuModel;
    MemoryModel memoryModel;
    NetworkModel networkModel;
    StorageModel storageModel;
    GPUModel gpuModel;  
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("cpuModel", &cpuModel);
    engine.rootContext()->setContextProperty("memoryModel", &memoryModel);
    engine.rootContext()->setContextProperty("networkModel", &networkModel);
    engine.rootContext()->setContextProperty("storageModel", &storageModel);
    engine.rootContext()->setContextProperty("gpuModel", &gpuModel);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);



    return app.exec();
}
