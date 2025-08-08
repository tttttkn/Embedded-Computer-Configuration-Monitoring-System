#include "modelcontroller.h"

ModelController::ModelController(QObject *parent) : QObject(parent)
{

    //Init
    updateCpuInfo();
    updateGpuInfo();
    updateMemoryInfo();
    updateNetworkInfo();
    updateStorageInfo();
    updateSystemInfo();

}

ModelController::~ModelController()
{
    cpuThread.quit();
    cpuThread.wait();

    gpuThread.quit();
    gpuThread.wait();

    memoryThread.quit();
    memoryThread.wait();

    networkThread.quit();
    networkThread.wait();

    storageThread.quit();
    storageThread.wait();

    systemThread.quit();
    systemThread.wait();
}

void ModelController::initServices()
{

    Logger::addLog("System monitoring initialized");

    m_cpuService.moveToThread(&cpuThread);
    connect(&m_cpuService, &CpuService::cpuInfoUpdated, &cpuModel, &CpuModel::updateCpuInfo);
    connect(&cpuModel, &CpuModel::cpuInfoUpdated, this, &ModelController::updateCpuInfo);
    cpuThread.start();
    QMetaObject::invokeMethod(&m_cpuService, "startMonitoring", Qt::QueuedConnection);


    m_gpuService.moveToThread(&gpuThread);
    connect(&m_gpuService, &GpuService::gpuInfoUpdated, &gpuModel, &GPUModel::updateGpuInfo);
    connect(&gpuModel, &GPUModel::gpuInfoUpdated, this, &ModelController::updateGpuInfo);
    gpuThread.start();
    QMetaObject::invokeMethod(&m_gpuService, "startMonitoring", Qt::QueuedConnection);

    m_memoryService.moveToThread(&memoryThread);
    connect(&m_memoryService, &MemoryService::memoryInfoUpdated, &memoryModel, &MemoryModel::updateMemoryInfo);
    connect(&memoryModel, &MemoryModel::memoryInfoUpdated, this, &ModelController::updateMemoryInfo);
    memoryThread.start();
    QMetaObject::invokeMethod(&m_memoryService, "startMonitoring", Qt::QueuedConnection);

    m_networkService.moveToThread(&networkThread);
    connect(&m_networkService, &NetworkService::networkInfoUpdated, &networkModel, &NetworkModel::updateNetworkInfo);
    connect(&networkModel, &NetworkModel::networkInfoUpdated, this, &ModelController::updateNetworkInfo);
    networkThread.start();
    QMetaObject::invokeMethod(&m_networkService, "startMonitoring", Qt::QueuedConnection);

    m_storageService.moveToThread(&storageThread);
    connect(&m_storageService, &StorageService::storageInfoUpdated, &storageModel, &StorageModel::updateStorageInfo);
    connect(&storageModel, &StorageModel::storageInfoUpdated, this, &ModelController::updateStorageInfo);
    storageThread.start();
    QMetaObject::invokeMethod(&m_storageService, "startMonitoring", Qt::QueuedConnection);

    m_systemService.moveToThread(&systemThread);
    connect(&m_systemService, &SystemService::staticSystemInfoUpdated, &systemModel, &SystemModel::updateStaticSystemInfo);
    connect(&systemModel, &SystemModel::staticSystemInfoUpdated, this, &ModelController::updateStaticSystemInfo);
    connect(&m_systemService, &SystemService::systemInfoUpdated, &systemModel, &SystemModel::updateSystemInfo);
    connect(&systemModel, &SystemModel::systemInfoUpdated, this, &ModelController::updateSystemInfo);
    systemThread.start();
    QMetaObject::invokeMethod(&m_systemService, "init", Qt::QueuedConnection);
    QMetaObject::invokeMethod(&m_systemService, "startMonitoring", Qt::QueuedConnection);

    

}


float ModelController::cpuTemp() const
{
    return cpuModel.getCpuTemperature();
}

QVariantList ModelController::cpuUsage() const
{
    return cpuModel.getCpuUsage();
}

float ModelController::lastCpuUsage() const
{
    if (cpuModel.getCpuUsage().isEmpty()) {
        return 0.0f; 
    }
    return cpuModel.getCpuUsage().last().toFloat();
}

float ModelController::cpuClock() const
{
    return cpuModel.getCpuClock();
}

int ModelController::totalProcesses() const
{
    return cpuModel.getTotalProcesses();
}
int ModelController::totalThreads() const
{
    return cpuModel.getTotalThreads();
}

void ModelController::updateCpuInfo()
{
    emit cpuUsageChanged();
    emit lastCpuUsageChanged();
    emit cpuTempChanged();
    emit cpuClockChanged();
    emit totalProcessesChanged();
    emit totalThreadsChanged();
}

QVariantMap ModelController::gpuInfo() const
{
    return gpuModel.getGpuInfo();
}

void ModelController::updateGpuInfo()
{
    emit gpuInfoChanged();
}

QVariantMap ModelController::memoryInfo() const
{
    return memoryModel.getMemoryInfo();
}

void ModelController::updateMemoryInfo()
{
    emit memoryInfoChanged();
}

QVariantMap ModelController::networkInfo() const
{
    return networkModel.getNetworkInfo();
}


void ModelController::updateNetworkInfo()
{
    emit networkInfoChanged();
}

QVariantMap ModelController::storageInfo() const
{
    return storageModel.getStorageInfo();
}

void ModelController::updateStorageInfo()
{
    emit storageInfoChanged();
}

QVariantMap ModelController::staticSystemInfo() const
{
    return systemModel.getStaticSystemInfo();
}

void ModelController::updateStaticSystemInfo()
{
    emit staticSystemInfoChanged();
}

void ModelController::updateSystemInfo()
{
    emit uptimeChanged();
}

QString ModelController::uptime() const
{
    return systemModel.getUptime();
}

// void ModelController::updateLogger()
// {
//     emit newLogChanged();
// }

// QString ModelController::newLog() const
// {
//     return Logger::getInstance()->newLog();
// }
