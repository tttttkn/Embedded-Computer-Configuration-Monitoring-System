#include "gpumodel.h"

GPUModel::GPUModel(QObject *parent) : QObject(parent)
{

}

void GPUModel::updateGpuInfo(const GpuInfo &info)
{
    m_gpuInfo["gpuMemory"] = info.gpuMemory;
    m_gpuInfo["temperature"] = info.temperature;
    m_gpuInfo["clockSpeedMax"] = info.clockSpeedMax;
    m_gpuInfo["clockSpeed"] = info.clockSpeed;

    emit gpuInfoUpdated();
}
