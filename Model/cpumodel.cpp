#include "cpumodel.h"

CpuModel::CpuModel(QObject *parent) : QObject(parent)
{
    sg_init(1);
}

CpuModel::~CpuModel()
{
    sg_shutdown();
}

void CpuModel::updateCpuUsage() 
{
    sg_cpu_percents* cpuStats = sg_get_cpu_percents(NULL);
    qDebug() << "CPU Usage (Total):" << cpuStats->user + cpuStats->kernel << "%";

    float totalUsage = cpuStats->user + cpuStats->kernel;
    totalUsage = qRound(totalUsage * 10) / 10.0f;

    m_cpuUsage.append(totalUsage);
    if (m_cpuUsage.size() > MAX_DATA_POINTS) {
        m_cpuUsage.removeFirst();
    }
}

void CpuModel::updateCpuTemperature() 
{
    QFile tempFile("/sys/class/thermal/thermal_zone0/temp");

    // QString appDir = QCoreApplication::applicationDirPath();
    // QFile tempFile(appDir + "/temp");
    if (!tempFile.open(QIODevice::ReadOnly)) {
        qDebug() << "Cannot open temperature file";
        return;
    }

    QTextStream in(&tempFile);
    QString tempStr = in.readLine();
    m_cpuTemp = tempStr.toInt(NULL) / 1000.0f;
    qDebug() << "CPU Temperature:" << m_cpuTemp << "°C";
}

void CpuModel::updateCpuClock() 
{
    QFile file("/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq");

    // QString appDir = QCoreApplication::applicationDirPath();
    // QFile file(appDir + "/scaling_cur_freq");

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Cannot open CPU frequency file:" << file.errorString();
        return;
    }

    QTextStream in(&file);
    QString freqStr = in.readLine();

    float freq_khz = freqStr.toFloat(NULL);
    qDebug() << "CPU Frequency:" << freq_khz / 1000.0f << "MHz";

    m_cpuClock = qRound(freq_khz / 1000.0f * 10) / 10.0f;
}

void CpuModel::updateTotalProcesses() 
{
    QProcess process;
    process.start("ps", {"-e", "--no-headers"});
    process.waitForFinished();
    
    QString output = process.readAllStandardOutput();
    qDebug() << "Total Processes Output:" << output.count('\n') + 1;
    m_totalProcesses = output.count('\n') + 1;
}

void CpuModel::updateTotalThreads() 
{
    QProcess process;
    process.start("ps", {"-eL", "--no-headers"});
    process.waitForFinished();
    
    QString output = process.readAllStandardOutput();
    qDebug() << "Total Threads Output:" << output.count('\n');
    m_totalThreads = output.count('\n');
}

