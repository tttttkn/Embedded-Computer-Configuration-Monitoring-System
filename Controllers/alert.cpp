#include "alert.h"
#include <QDateTime>

Alert* Alert::getInstance()
{
    static Alert instance; // Singleton instance
    return &instance;
}

QVariantMap Alert::newAlert() const {
    return m_newAlert;
}

void Alert::addAlert(const QString &type, const QString &message) {
    getInstance()->addAlertImpl(type, message);
}

void Alert::addAlertImpl(const QString &type, const QString &message) {
    m_newAlert["type"] = type;
    m_newAlert["message"] = message;
    emit newAlertChanged();
}

void Alert::startAlertCpuWarn(const float threshold, const float cpuUsage) {

    if (cpuUsage > threshold && m_isCpuWarn == false) 
    {
        addAlert("WARNING", QString("[Warning] CPU usage is high: %1% > %2%").arg(cpuUsage).arg(threshold));
        m_isCpuWarn = true;
    }
}

void Alert::startAlertCpuCrit(const float threshold, const float cpuUsage) {
    if (cpuUsage > threshold && m_isCpuCrit == false) {
        addAlert("CRITICAL", QString("[Critical] CPU usage is critical: %1% > %2%").arg(cpuUsage).arg(threshold));
        m_isCpuCrit = true;
    }
}

void Alert::startAlertRamWarn(const float threshold, const float ramUsage) {
    if (ramUsage > threshold && m_isRamWarn == false) {
        addAlert("WARNING", QString("[Warning] RAM usage is high: %1% > %2%").arg(ramUsage).arg(threshold));
        m_isRamWarn = true;
    }
}
