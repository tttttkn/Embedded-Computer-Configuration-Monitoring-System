#include "cpumodel.h"

CpuModel::CpuModel(QObject *parent) : QObject(parent)
{
}

CpuModel::~CpuModel()
{
}

void CpuModel::updateCpuInfo(CpuService::CpuInfo info)
{
    qDebug() << "CPU Info Updated:" 
           << "Usage:" << info.cpuUsage 
           << "Temperature:" << info.cpuTemperature 
           << "Clock:" << info.cpuClock 
           << "Processes:" << info.totalProcesses 
           << "Threads:" << info.totalThreads;

    m_cpuUsage = info.cpuUsage; 
    m_cpuTemp = info.cpuTemperature;
    m_cpuClock = info.cpuClock;
    m_totalProcesses = info.totalProcesses;
    m_totalThreads = info.totalThreads;
}


