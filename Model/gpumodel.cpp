#include "gpumodel.h"

GPUModel::GPUModel(QObject *parent) : QObject(parent)
{
    m_timer.start(5000); 

    //init
    updateGpuInfo();
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

    newInfo["gpuMemory"] = runCommand("vcgencmd get_mem gpu");
    newInfo["cpuMemory"] = runCommand("vcgencmd get_mem arm");
    newInfo["temperature"] = runCommand("vcgencmd measure_temp");
    newInfo["clockSpeed"] = runCommand("vcgencmd measure_clock v3d");

    m_gpuInfo = newInfo;

    qDebug() << "----------------------------------";
    qDebug() << "GPU Info:";
    for (const QString &key : m_gpuInfo.keys()) {
        qDebug() << key << ":" << m_gpuInfo.value(key).toString();
    }


}