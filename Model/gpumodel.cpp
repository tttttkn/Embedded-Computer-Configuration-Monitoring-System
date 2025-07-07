#include "gpumodel.h"

GPUModel::GPUModel(QObject *parent) : QObject(parent)
{

}



QString GPUModel::runCommand(const QString &cmd)
{
    QProcess process;
    process.start("bash", QStringList() << "-c" << cmd);
    process.waitForFinished();
    return process.readAllStandardOutput().trimmed();
}

float GPUModel::convertMemToFloat(const QString &str) {

    if (!str.isEmpty()) {
        // Loại bỏ "gpu=" và "M"
        QString numberStr = str.split('=')[1].replace("M", ""); 
        // Chuyển thành số nguyên
        float number{0};
        number = numberStr.toFloat();

        return number;  // Trả về 76
    }

    return -1;  // Nếu lỗi
}

float GPUModel::convertTempToFloat(const QString &str) {

    if (!str.isEmpty()) {
        // Loại bỏ "gpu=" và "M"
        QString numberStr = str.split('=')[1].replace("'C", ""); 
        // Chuyển thành số nguyên
        float number{0};
        number = numberStr.toFloat();

        return number;  // Trả về 76
    }

    return -1;  // Nếu lỗi
}

float GPUModel::convertFreqToFloat(const QString &str) {

    if (!str.isEmpty()) {
        QString numberStr = str.split('=')[1]; 
        float number{0};
        number = numberStr.toFloat();

        return number;  
    }

    return -1;  // Nếu lỗi
}

void GPUModel::updateGpuInfo()
{
    QVariantMap gpuInfo;

    gpuInfo["gpuMemory"] =convertMemToFloat(runCommand("vcgencmd get_mem gpu"));
    // gpuInfo["cpuMemory"] = convertMemToFloat(runCommand("vcgencmd get_mem arm"));
    gpuInfo["temperature"] = convertTempToFloat(runCommand("vcgencmd measure_temp"));
    gpuInfo["clockSpeedMax"] = convertFreqToFloat(runCommand("vcgencmd get_config core_freq"));
    gpuInfo["clockSpeed"] = convertFreqToFloat(runCommand("vcgencmd get_config gpu_freq"));

    m_gpuInfo = gpuInfo;

    qDebug() << "----------------------------------";
    qDebug() << "GPU Info:";
    for (const QString &key : m_gpuInfo.keys()) {
        qDebug() << key << ":" << m_gpuInfo.value(key).toString();
    }


}