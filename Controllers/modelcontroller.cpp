#include "modelcontroller.h"

ModelController::ModelController(QObject *parent) : QObject(parent)
{
    connect(&m_timer, &QTimer::timeout, this, &ModelController::updateCpuInfo);
    connect(&m_timer, &QTimer::timeout, this, &ModelController::updateGpuInfo);
    connect(&m_timer, &QTimer::timeout, this, &ModelController::updateMemoryInfo);
    connect(&m_timer, &QTimer::timeout, this, &ModelController::updateNetworkInfo);
    m_timer.start(1000);


    //Init
    updateCpuInfo();
}

ModelController::~ModelController()
{
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
    cpuModel.updateCpuUsage();
    emit cpuUsageChanged();
    emit lastCpuUsageChanged();

    cpuModel.updateCpuTemperature();
    emit cpuTempChanged();

    cpuModel.updateCpuClock();
    emit cpuClockChanged();
    
    cpuModel.updateTotalProcesses();
    emit totalProcessesChanged();
    
    cpuModel.updateTotalThreads();
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
