#include "modelcontroller.h"

ModelController::ModelController(QObject *parent) : QObject(parent)
{

    connect(&m_cpuService, &CpuService::cpuInfoUpdated, &cpuModel, &CpuModel::updateCpuInfo);
    m_cpuService.moveToThread(&cpuThread);
    cpuThread.start();
    QMetaObject::invokeMethod(&m_cpuService, "startMonitoring", Qt::QueuedConnection);

    connect(&m_timer, &QTimer::timeout, this, &ModelController::updateCpuInfo);
    connect(&m_timer, &QTimer::timeout, this, &ModelController::updateGpuInfo);
    connect(&m_timer, &QTimer::timeout, this, &ModelController::updateMemoryInfo);
    connect(&m_timer, &QTimer::timeout, this, &ModelController::updateNetworkInfo);
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
    QMetaObject::invokeMethod(&m_cpuService, "stopMonitoring", Qt::QueuedConnection);
    cpuThread.requestInterruption();
    cpuThread.quit();
    cpuThread.wait();
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
    gpuModel.updateGpuInfo();
    emit gpuInfoChanged();
}

QVariantMap ModelController::memoryInfo() const
{
    return memoryModel.getMemoryInfo();
}

void ModelController::updateMemoryInfo()
{
    memoryModel.updateMemoryInfo();
    emit memoryInfoChanged();
}

QVariantMap ModelController::networkInfo() const
{
    return networkModel.getNetworkInfo();
}

void ModelController::updateNetworkInfo()
{
    networkModel.updateNetworkInfo();
    emit networkInfoChanged();
}

QVariantMap ModelController::storageInfo() const
{
    return storageModel.getStorageInfo();
}

void ModelController::updateStorageInfo()
{
    storageModel.updateStorageInfo();
    emit storageInfoChanged();
}
