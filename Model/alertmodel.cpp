// AlertModel.cpp

#include "alertmodel.h"
#include <QDateTime>

AlertModel* AlertModel::getInstance()
{
    static AlertModel instance; // Singleton instance
    return &instance;
}

QVariantMap AlertModel::newAlert() const {
    return m_newAlert;
}

void AlertModel::addAlert(const QString &type, const QString &message) {
    getInstance()->addAlertImpl(type, message);
}

void AlertModel::addAlertImpl(const QString &type, const QString &message) {
    m_newAlert["type"] = type;
    m_newAlert["message"] = message;
    emit newAlertChanged();
}

void AlertModel::startAlertCpuWarn(const float threshold, const float cpuUsage) {

    if (cpuUsage > threshold && m_isCpuWarn == false) 
    {
        addAlert("WARNING", QString("CPU usage is high: %1%").arg(cpuUsage));
        m_isCpuWarn = true;
    }
}

void AlertModel::startAlertCpuCrit(const float threshold, const float cpuUsage) {
    if (cpuUsage > threshold && m_isCpuCrit == false) {
        addAlert("CRITICAL", QString("CPU usage is critical: %1%").arg(cpuUsage));
        m_isCpuCrit = true;
    }
}

void AlertModel::startAlertRamWarn(const float threshold, const float ramUsage) {
    if (ramUsage > threshold && m_isRamWarn == false) {
        addAlert("WARNING", QString("RAM usage is high: %1%").arg(ramUsage));
        m_isRamWarn = true;
    }
}
