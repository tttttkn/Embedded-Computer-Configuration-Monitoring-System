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

#include "i_cpuservice.h"

#define MAX_DATA_POINTS 20

class CpuService :  public QObject
                    // public ICpuService
{
    Q_OBJECT
public:
    explicit CpuService(QObject *parent = nullptr);
    ~CpuService();
    struct CpuInfo
    {
        float cpuClock{};
        int totalProcesses{};
        int totalThreads{};
        QVariantList cpuUsage{};
        float cpuTemperature{};
    };

    void updateCpuUsage();
    void updateCpuTemperature();
    void updateCpuClock();
    void updateTotalProcesses();
    void updateTotalThreads();

public slots:
    void startMonitoring();
    void stopMonitoring();

signals:
    void cpuInfoUpdated(CpuService::CpuInfo info);

private:
    CpuInfo m_cpuInfo;
    bool m_isMonitoring{false};

};

#endif // CPUSERVICE_H