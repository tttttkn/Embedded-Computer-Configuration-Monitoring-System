#include "memorymodel.h"

MemoryModel::MemoryModel(QObject *parent) : QObject(parent)
{
}

void MemoryModel::updateMemoryInfo(const MemoryInfo &info)
{
    m_memoryInfo["usedMemory"] = info.usedMemory;
    m_memoryInfo["availableMemory"] = info.availableMemory;
    m_memoryInfo["ramUsage"] = info.ramUsage;
    m_memoryInfo["swapUsed"] = info.swapUsed;
    m_memoryInfo["swapAvailable"] = info.swapAvailable;
    m_memoryInfo["swapUsage"] = info.swapUsage;

    emit memoryInfoUpdated();
}
