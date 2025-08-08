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
