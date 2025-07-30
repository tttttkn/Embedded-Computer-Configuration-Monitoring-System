#ifndef CPUSERVICE_H
#define CPUSERVICE_H

#include <QObject>
#include <QThread>
#include <QFile>
#include <QDebug>
#include <QProcess>
#include <QDir>
#include <statgrab.h>
#include <cpufreq.h>


#define MAX_DATA_POINTS 20

struct CpuInfo
{
    float cpuClock{};
    int totalProcesses{};
    int totalThreads{};
    QVariantList cpuUsage{};
    float cpuTemperature{};
};
Q_DECLARE_METATYPE(CpuInfo)

class CpuService :  public QObject
{
    Q_OBJECT
public:
    explicit CpuService(QObject *parent = nullptr);
    ~CpuService();


    void updateCpuUsage();
    void updateCpuTemperature();
    void updateCpuClock();
    void updateTotalProcesses();
    void updateTotalThreads();

public slots:
    void startMonitoring();
    void stopMonitoring();

signals:
    void cpuInfoUpdated(const CpuInfo &info);

private:
    CpuInfo m_cpuInfo;
    bool m_isMonitoring{false};

};

#endif // CPUSERVICE_H