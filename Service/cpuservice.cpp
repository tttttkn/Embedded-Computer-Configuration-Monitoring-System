#include "cpuservice.h"

CpuService::CpuService(QObject *parent) : QObject(parent)
{
}

CpuService::~CpuService()
{
    stopMonitoring();
}

void CpuService::updateCpuUsage() 
{
    sg_init(1);

    sg_cpu_percents* cpuStats = sg_get_cpu_percents(NULL);
    // qDebug() << "CPU Usage (Total):" << cpuStats->user + cpuStats->kernel << "%";

    float totalUsage = cpuStats->user + cpuStats->kernel;
    totalUsage = qRound(totalUsage * 10) / 10.0f;

    m_cpuInfo.cpuUsage.append(totalUsage);
    if (m_cpuInfo.cpuUsage.size() > MAX_DATA_POINTS) {
        m_cpuInfo.cpuUsage.removeFirst();
    }

    sg_shutdown();

}

void CpuService::updateCpuTemperature() 
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
    m_cpuInfo.cpuTemperature = tempStr.toInt(NULL) / 1000.0f;
    // qDebug() << "CPU Temperature:" << m_cpuInfo.cpuTemperature << "°C";
}

void CpuService::updateCpuClock() 
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
    // qDebug() << "CPU Frequency:" << freq_khz / 1000.0f << "MHz";

    m_cpuInfo.cpuClock = qRound(freq_khz / 1000.0f * 10) / 10.0f;
}

void CpuService::updateTotalProcesses() 
{

    QDir procDir("/proc");
    QStringList processDirs = procDir.entryList(QDir::Dirs);

    int count = 0;
    for (const QString &dir : processDirs) {
        bool isPid;
        dir.toInt(&isPid);
        if (isPid) {
            count++;
        }
    }
    m_cpuInfo.totalProcesses = count;
}

void CpuService::updateTotalThreads() 
{
    QDir procDir("/proc");
    QStringList processDirs = procDir.entryList(QDir::Dirs);

    int totalThreads = 0;
    for (const QString &dir : processDirs) {
        bool isPid;
        dir.toInt(&isPid);
        if (!isPid) continue;

        QFile statusFile("/proc/" + dir + "/status");
        if (statusFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&statusFile);
            while (true) {
                QString line = in.readLine();
                if (line.startsWith("Threads:")) {
                    totalThreads += line.split("\t").last().toInt();
                    break;
                }
            }
            statusFile.close();
        }
    }
    m_cpuInfo.totalThreads = totalThreads;
}

void CpuService::startMonitoring() 
{
    m_isMonitoring = true;
    // qDebug() << "Starting CPU monitoring...";
    while (m_isMonitoring) {
        updateCpuUsage();
        updateCpuTemperature();
        updateCpuClock();
        updateTotalProcesses();
        updateTotalThreads();

        // qDebug() << "CPU Info Updated:";
        emit cpuInfoUpdated(m_cpuInfo);

        QThread::sleep(1); // Sleep for 1 second before the next update
    }

}

void CpuService::stopMonitoring() 
{
    m_isMonitoring = false;
    // qDebug() << "CPU monitoring stopped.";
}

