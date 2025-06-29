#include "memorymodel.h"
#include <QStorageInfo>

MemoryModel::MemoryModel(QObject *parent) : QObject(parent)
{
    connect(&m_timer, &QTimer::timeout, this, &MemoryModel::updateMemoryInfo);
    m_timer.start(5000); 
    updateMemoryInfo();
}

QVariantMap MemoryModel::memoryInfo() const
{
    return m_memoryInfo;
}

void MemoryModel::updateMemoryInfo()
{
    getMemoryInfo();
    emit memoryInfoChanged();
}

void MemoryModel::getMemoryInfo() {

    struct sysinfo info;
    if (sysinfo(&info) == -1) {
        perror("Lỗi sysinfo");
        return;
    }
    // Convert to MB
    m_memoryInfo["usedMemory"] = (info.totalram - info.freeram) / 1024.0 / 1024.0;
    m_memoryInfo["availableMemory"] = info.freeram / 1024.0 / 1024.0;
    m_memoryInfo["ramUsage"] = (m_memoryInfo["usedMemory"].toFloat() / (info.totalram / 1024.0 / 1024.0)) * 100.0;
    m_memoryInfo["swapUsed"] = (info.totalswap - info.freeswap) / 1024.0 / 1024.0;
    m_memoryInfo["swapAvailable"] = info.freeswap / 1024.0 / 1024.0;
    m_memoryInfo["swapUsage"] = (m_memoryInfo["swapUsed"].toFloat() / (info.totalswap / 1024.0 / 1024.0)) * 100.0;
    
    
    // Debug output
    qDebug() << "----------------------------------";
    qDebug() << "Memory Info:";
    qDebug() << "Used Memory:" << m_memoryInfo["usedMemory"].toFloat() << "MB";
    qDebug() << "Available Memory:" << m_memoryInfo["availableMemory"].toFloat() << "MB";
    qDebug() << "RAM Usage:" << m_memoryInfo["ramUsage"].toFloat() << "%";
    qDebug() << "Used Swap:" << m_memoryInfo["swapUsed"].toFloat() << "MB";
    qDebug() << "Available Swap:" << m_memoryInfo["swapAvailable"].toFloat() << "MB";
    qDebug() << "Swap Usage:" << m_memoryInfo["swapUsage"].toFloat() << "%";
    qDebug() << "----------------------------------";




}
