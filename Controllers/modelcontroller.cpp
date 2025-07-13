#include "modelcontroller.h"

ModelController::ModelController(QObject *parent) : QObject(parent)
{


    // connect(&m_timer, &QTimer::timeout, this, &ModelController::updateCpuInfo);
    // connect(&m_timer, &QTimer::timeout, this, &ModelController::updateGpuInfo);
    // connect(&m_timer, &QTimer::timeout, this, &ModelController::updateMemoryInfo);
    // connect(&m_timer, &QTimer::timeout, this, &ModelController::updateNetworkInfo);
    connect(&m_timer, &QTimer::timeout, this, &ModelController::updateStorageInfo);
    m_timer.start(1000);


    //Init
    updateCpuInfo(); 
    updateGpuInfo();
    updateMemoryInfo();
    updateNetworkInfo();
    updateStorageInfo();
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

    // storageThread.quit();
    // storageThread.wait();
}

void ModelController::initServices()
{
    m_cpuService.moveToThread(&cpuThread);
    connect(&m_cpuService, &CpuService::cpuInfoUpdated, &cpuModel, &CpuModel::updateCpuInfo);
    connect(&m_cpuService, &CpuService::cpuInfoUpdated, this, &ModelController::updateCpuInfo);
    cpuThread.start();
    QMetaObject::invokeMethod(&m_cpuService, "startMonitoring", Qt::QueuedConnection);


    m_gpuService.moveToThread(&gpuThread);
    connect(&m_gpuService, &GpuService::gpuInfoUpdated, &gpuModel, &GPUModel::updateGpuInfo);
    connect(&m_gpuService, &GpuService::gpuInfoUpdated, this, &ModelController::updateGpuInfo);
    gpuThread.start();
    QMetaObject::invokeMethod(&m_gpuService, "startMonitoring", Qt::QueuedConnection);

    m_memoryService.moveToThread(&memoryThread);
    connect(&m_memoryService, &MemoryService::memoryInfoUpdated, &memoryModel, &MemoryModel::updateMemoryInfo);
    connect(&m_memoryService, &MemoryService::memoryInfoUpdated, this, &ModelController::updateMemoryInfo);
    memoryThread.start();
    QMetaObject::invokeMethod(&m_memoryService, "startMonitoring", Qt::QueuedConnection);

    m_networkService.moveToThread(&networkThread);
    connect(&m_networkService, &NetworkService::networkInfoUpdated, &networkModel, &NetworkModel::updateNetworkInfo);
    connect(&m_networkService, &NetworkService::networkInfoUpdated, this, &ModelController::updateNetworkInfo);
    networkThread.start();
    QMetaObject::invokeMethod(&m_networkService, "startMonitoring", Qt::QueuedConnection);

    m_storageService.moveToThread(&storageThread);
    connect(&m_storageService, &StorageService::storageInfoUpdated, &storageModel, &StorageModel::updateStorageInfo);
    connect(&m_storageService, &StorageService::storageInfoUpdated, this, &ModelController::updateStorageInfo);
    storageThread.start();
    QMetaObject::invokeMethod(&m_storageService, "startMonitoring", Qt::QueuedConnection);
}


float ModelController::cpuTemp() const
{
    return cpuModel.getCpuTemperature();
}

QVariantList ModelController::cpuUsage()
{
    return cpuModel.getCpuUsage();
}

float ModelController::lastCpuUsage()
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
    // cpuModel.updateCpuUsage();
    emit cpuUsageChanged();
    emit lastCpuUsageChanged();

    // cpuModel.updateCpuTemperature();
    emit cpuTempChanged();

    // cpuModel.updateCpuClock();
    emit cpuClockChanged();
    
    // cpuModel.updateTotalProcesses();
    emit totalProcessesChanged();
    
    // cpuModel.updateTotalThreads();
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
    // networkModel.updateNetworkInfo();
    emit networkInfoChanged();
}

QVariantMap ModelController::storageInfo() const
{
    return storageModel.getStorageInfo();
}

void ModelController::updateStorageInfo()
{
    // storageModel.updateStorageInfo();
    emit storageInfoChanged();
}
