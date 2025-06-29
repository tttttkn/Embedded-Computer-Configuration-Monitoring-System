#include "gpumodel.h"

GPUModel::GPUModel(QObject *parent) : QObject(parent)
{
    connect(&m_timer, &QTimer::timeout, this, &GPUModel::updateGpuInfo);
    m_timer.start(5000); 

    //init
    updateGpuInfo();
}

QVariantMap GPUModel::gpuInfo() const
{
    return m_gpuInfo;
}

QString GPUModel::runCommand(const QString &cmd)
{
    QProcess process;
    process.start("bash", QStringList() << "-c" << cmd);
    process.waitForFinished();
    return process.readAllStandardOutput().trimmed();
}

void GPUModel::updateGpuInfo()
{
    QVariantMap newInfo;

    // Lấy thông số GPU
    newInfo["gpuMemory"] = runCommand("vcgencmd get_mem gpu");
    newInfo["cpuMemory"] = runCommand("vcgencmd get_mem arm");
    newInfo["temperature"] = runCommand("vcgencmd measure_temp");
    newInfo["clockSpeed"] = runCommand("vcgencmd measure_clock v3d");

    qDebug() << "----------------------------------";
    qDebug() << "GPU Info:";
    for (const QString &key : newInfo.keys()) {
        qDebug() << key << ":" << newInfo.value(key).toString();
    }

    if (m_gpuInfo != newInfo) {
        m_gpuInfo = newInfo;
        emit gpuInfoChanged();
    }
}