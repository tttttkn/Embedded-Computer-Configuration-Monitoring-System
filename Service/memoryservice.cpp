#include "memoryservice.h"

MemoryService::MemoryService(QObject *parent) : QObject(parent) {}
MemoryService::~MemoryService() { stopMonitoring(); }

void MemoryService::updateMemoryInfo()
{
    struct sysinfo info;
    if (sysinfo(&info) == -1) {
        qWarning() << "error sysinfo";
        return;
    }
    m_memoryInfo.usedMemory = (info.totalram - info.freeram) / 1024.0 / 1024.0;
    m_memoryInfo.availableMemory = info.freeram / 1024.0 / 1024.0;
    m_memoryInfo.ramUsage = (m_memoryInfo.usedMemory / (info.totalram / 1024.0 / 1024.0)) * 100.0;
    m_memoryInfo.swapUsed = (info.totalswap - info.freeswap) / 1024.0 / 1024.0;
    m_memoryInfo.swapAvailable = info.freeswap / 1024.0 / 1024.0;
    m_memoryInfo.swapUsage = (m_memoryInfo.swapUsed / (info.totalswap / 1024.0 / 1024.0)) * 100.0;

    qDebug() << "Memory usage:" << m_memoryInfo.usedMemory << "MB"
             << "Available:" << m_memoryInfo.availableMemory << "MB"
             << "RAM Usage:" << m_memoryInfo.ramUsage << "%"
             << "Swap Used:" << m_memoryInfo.swapUsed << "MB"
             << "Swap Available:" << m_memoryInfo.swapAvailable << "MB"
             << "Swap Usage:" << m_memoryInfo.swapUsage << "%";
}

void MemoryService::startMonitoring()
{
    m_isMonitoring = true;
    // qDebug() << "Starting Memory monitoring...";
    while (m_isMonitoring) {
        updateMemoryInfo();
        emit memoryInfoUpdated(m_memoryInfo);
        QThread::sleep(1);
    }
}

void MemoryService::stopMonitoring()
{
    m_isMonitoring = false;
    // qDebug() << "Memory monitoring stopped.";
}