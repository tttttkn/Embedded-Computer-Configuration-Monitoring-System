#include "gpuservice.h"

GpuService::GpuService(QObject *parent) : QObject(parent) 
{

}
GpuService::~GpuService() 
{
    stopMonitoring();
}

QString GpuService::runCommand(const QString &cmd)
{
    QProcess process;
    process.start("bash", QStringList() << "-c" << cmd);
    process.waitForFinished();
    return process.readAllStandardOutput().trimmed();
}

float GpuService::convertMemToFloat(const QString &str) {
    if (!str.isEmpty()) {
        QString numberStr = str.split('=')[1].replace("M", "");
        return numberStr.toFloat();
    }
    return -1;
}

float GpuService::convertTempToFloat(const QString &str) {
    if (!str.isEmpty()) {
        QString numberStr = str.split('=')[1].replace("'C", "");
        return numberStr.toFloat();
    }
    return -1;
}

float GpuService::convertFreqToFloat(const QString &str) {
    if (!str.isEmpty()) {
        QString numberStr = str.split('=')[1];
        return numberStr.toFloat();
    }
    return -1;
}

void GpuService::updateGpuInfo()
{
    m_gpuInfo.gpuMemory = convertMemToFloat(runCommand("vcgencmd get_mem gpu"));
    m_gpuInfo.temperature = convertTempToFloat(runCommand("vcgencmd measure_temp"));
    m_gpuInfo.clockSpeed = convertFreqToFloat(runCommand("vcgencmd get_config gpu_freq"));
}

void GpuService::startMonitoring()
{
    m_isMonitoring = true;
    m_gpuInfo.clockSpeedMax = convertFreqToFloat(runCommand("vcgencmd get_config core_freq"));

    // qDebug() << "Starting GPU monitoring...";
    while (m_isMonitoring) {
        updateGpuInfo();
        emit gpuInfoUpdated(m_gpuInfo);
        // qDebug() << "GPU Info Updated:" << m_gpuInfo.gpuMemory << "MB" << m_gpuInfo.temperature << "°C" 
        //          << m_gpuInfo.clockSpeedMax << "MHz" << m_gpuInfo.clockSpeed << "MHz";
        QThread::sleep(1);
    }
}

void GpuService::stopMonitoring()
{
    m_isMonitoring = false;
    // qDebug() << "GPU monitoring stopped.";
}