#include "cpumodel.h"

CpuModel::CpuModel(QObject *parent) : QObject(parent)
{
    connect(&m_timer, &QTimer::timeout, this, &CpuModel::updateCpuTemp);
    connect(&m_timer, &QTimer::timeout, this, &CpuModel::updateCpuUsage);
    connect(&m_timer, &QTimer::timeout, this, &CpuModel::updateCpuClock);
    connect(&m_timer, &QTimer::timeout, this, &CpuModel::updateTotalProcesses);
    connect(&m_timer, &QTimer::timeout, this, &CpuModel::updateTotalThreads);
    m_timer.start(1000); 


    sg_init(1);

}

CpuModel::~CpuModel()
{
    sg_shutdown();
}

float CpuModel::cpuTemp() const
{
    return m_cpuTemp;
}

QVariantList CpuModel::cpuUsage() const
{
    return m_cpuUsage;
}

float CpuModel::lastCpuUsage() const
{
    if (m_cpuUsage.isEmpty()) {
        return 0.0f;  // Trả về 0 nếu không có dữ liệu
    }
    return m_cpuUsage.last().toFloat();  // Trả về giá trị cuối cùng trong mảng dưới dạng float
}

float CpuModel::cpuClock() const
{
     return m_cpuClock;
}

int CpuModel::totalProcesses() const
{
    return m_totalProcesses;
}

int CpuModel::totalThreads() const
{
    return m_totalThreads;
}

void CpuModel::updateCpuTemp()
{
    m_cpuTemp = getCpuTemperature();
    emit cpuTempChanged();
}

void CpuModel::updateCpuUsage()
{
    float newCpuUsage = getCpuUsage();
    
    m_cpuUsage.append(newCpuUsage);  // Append the latest usage to the vector
    // Giới hạn số điểm dữ liệu
    if (m_cpuUsage.size() > MAX_DATA_POINTS) {
        m_cpuUsage.removeFirst();
    }
    emit cpuUsageChanged();
    emit lastCpuUsageChanged();  // Emit signal for the last CPU usage
}

void CpuModel::updateCpuClock()
{
    m_cpuClock = getCpuClock();
    emit cpuClockChanged();
}

void CpuModel::updateTotalProcesses()
{
    m_totalProcesses = getTotalProcesses();
    emit totalProcessesChanged();
}

void CpuModel::updateTotalThreads()
{
    m_totalThreads = getTotalThreads();
    emit totalThreadsChanged();
}



float CpuModel::getCpuUsage() const
{
    sg_cpu_percents* cpuStats = sg_get_cpu_percents(NULL);
    qDebug() << "CPU Usage (Total):" << cpuStats->user + cpuStats->kernel << "%";

    float totalUsage = cpuStats->user + cpuStats->kernel;
    return qRound(totalUsage * 10) / 10.0f;
}

float CpuModel::getCpuTemperature() const
{
    // QFile tempFile("/sys/class/thermal/thermal_zone0/temp");

    QString appDir = QCoreApplication::applicationDirPath();
    QFile tempFile(appDir + "/temp");
    if (!tempFile.open(QIODevice::ReadOnly)) {
        qDebug() << "Cannot open temperature file";
        return 0.0f;
    }

    QTextStream in(&tempFile);
    QString tempStr = in.readLine();
    float temp = tempStr.toInt(NULL) / 1000.0f;  // Chuyển từ millidegree C sang degree C
    qDebug() << "CPU Temperature:" << temp << "°C";
    return qRound(temp * 10) / 10.0f;
}

float CpuModel::getCpuClock() const
{
    // QFile file("/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq");

    QString appDir = QCoreApplication::applicationDirPath();
    QFile file(appDir + "/scaling_cur_freq");

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Cannot open CPU frequency file:" << file.errorString();
        return 0.0f;
    }

    QTextStream in(&file);
    QString freqStr = in.readLine();

    float freq_khz = freqStr.toFloat(NULL);
    qDebug() << "CPU Frequency:" << freq_khz / 1000.0f << "MHz";

    return qRound(freq_khz / 1000.0f * 10) / 10.0f;  // Chuyển từ kHz sang MHz
}

int CpuModel::getTotalProcesses() const 
{
    QProcess process;
    process.start("ps", {"-e", "--no-headers"});
    process.waitForFinished();
    
    QString output = process.readAllStandardOutput();
    qDebug() << "Total Processes Output:" << output.count('\n') + 1;
    return output.count('\n') + 1;  // Đếm số dòng
}

int CpuModel::getTotalThreads() const 
{
    QProcess process;
    process.start("ps", {"-eL", "--no-headers"});
    process.waitForFinished();
    
    QString output = process.readAllStandardOutput();
    qDebug() << "Total Threads Output:" << output.count('\n');
    return output.count('\n');  // Mỗi dòng là 1 thread
}

