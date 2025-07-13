#include "cpumodel.h"

CpuModel::CpuModel(QObject *parent) : QObject(parent)
{
}

CpuModel::~CpuModel()
{
}

void CpuModel::updateCpuInfo(const CpuInfo &info)
{
    m_cpuUsage = info.cpuUsage; 
    m_cpuTemp = info.cpuTemperature;
    m_cpuClock = info.cpuClock;
    m_totalProcesses = info.totalProcesses;
    m_totalThreads = info.totalThreads;

}


