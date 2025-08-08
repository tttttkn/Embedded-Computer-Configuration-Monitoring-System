#include "systemservice.h"
#include "QFile"
#include "../Controllers/logger.h"

SystemService::SystemService(QObject *parent) : QObject(parent) {}
SystemService::~SystemService() 
{
    stopMonitoring();
}

void SystemService::init()
{
    // Initialize system information
    m_staticSystemInfo.hostname = QHostInfo::localHostName();
    m_staticSystemInfo.os = QSysInfo::prettyProductName();
    m_staticSystemInfo.kernelVersion = QSysInfo::kernelVersion();
    // qDebug() << "Static System Info:" << m_staticSystemInfo.hostname
    //          << m_staticSystemInfo.os
    //          << m_staticSystemInfo.kernelVersion;
    emit staticSystemInfoUpdated(m_staticSystemInfo);
}

void SystemService::calculateUptime()
{
    QFile file("/proc/uptime");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return ;

    QTextStream in(&file);
    QString line = in.readLine();
    file.close();

    QStringList parts = line.split(' ');
    if (parts.size() < 1)
        return ;

    bool ok;
    double uptimeSeconds = parts[0].toDouble(&ok);
    if (!ok) return;

    int days = uptimeSeconds / 86400;
    int hours = ((int)uptimeSeconds % 86400) / 3600;
    int minutes = ((int)uptimeSeconds % 3600) / 60;
    int seconds = ((int)uptimeSeconds % 60);

    m_uptime = QString("%1D %2H %3M %4S")
            .arg(days).arg(hours).arg(minutes).arg(seconds);
}

void SystemService::startMonitoring()
{
    m_isMonitoring = true;
    // qDebug() << "Starting Storage monitoring...";
    while (m_isMonitoring) {
        calculateUptime();
        // Logger::addLog("Uptime updated: " + m_uptime);
        emit systemInfoUpdated(m_uptime);
        QThread::sleep(1);
    }
}

void SystemService::stopMonitoring()
{
    m_isMonitoring = false;
    // Stop monitoring system information
}