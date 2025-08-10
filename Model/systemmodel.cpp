#include "systemmodel.h"

SystemModel::SystemModel(QObject *parent)
    : QObject(parent)
{
}

void SystemModel::updateStaticSystemInfo(const StaticSystemInfo &info)
{
    m_staticSystemInfo["hostname"] = info.hostname;
    m_staticSystemInfo["os"] = info.os;
    m_staticSystemInfo["kernelVersion"] = info.kernelVersion;

    emit staticSystemInfoUpdated();
}

void SystemModel::updateSystemInfo(const QString uptime)
{
    m_uptime = uptime;
    emit systemInfoUpdated();
}

void SystemModel::setCpuWarn(int value)
{
    if (m_cpuWarn != value) {
        m_cpuWarn = value;
        Logger::addLog(QString("CPU warning level set to %1 %").arg(value));
    }
}

void SystemModel::setCpuCrit(int value)
{
    if (m_cpuCrit != value) {
        m_cpuCrit = value;
        Logger::addLog(QString("CPU critical level set to %1 %").arg(value));
    }
}

void SystemModel::setRamWarn(int value)
{
    if (m_ramWarn != value) {
        m_ramWarn = value;
        Logger::addLog(QString("RAM warning level set to %1 %").arg(value));
    }
}
