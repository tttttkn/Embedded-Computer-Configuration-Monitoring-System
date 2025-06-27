#include "cpumodel.h"

CpuModel::CpuModel(QObject *parent) : QObject(parent), m_cpuTemp(0)
{
    connect(&m_timer, &QTimer::timeout, this, &CpuModel::updateCpuTemp);
    connect(&m_timer, &QTimer::timeout, this, &CpuModel::updateCpuUsage);
    m_timer.start(1000); // Cập nhật mỗi 2 giây
}

float CpuModel::cpuTemp() const
{
    return m_cpuTemp;
}

float CpuModel::cpuUsage() const
{
    return m_cpuUsage;
}

void CpuModel::updateCpuTemp()
{
    m_cpuTemp = qrand() % 100;
    emit cpuTempChanged();
}

void CpuModel::updateCpuUsage()
{
    m_cpuUsage = qrand() % 100;
    emit cpuUsageChanged();
}
