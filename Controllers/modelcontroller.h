#ifndef MODELCONTROLLER_H
#define MODELCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <Model/cpumodel.h>
#include <Model/memorymodel.h>
#include <Model/networkmodel.h>
#include <Model/storagemodel.h>
#include <Model/gpumodel.h>

#include "Service/cpuservice.h"

class ModelController : public QObject
{
    Q_OBJECT
    //Cpu information
    Q_PROPERTY(float cpuTemp READ cpuTemp NOTIFY cpuTempChanged)
    Q_PROPERTY(QVariantList cpuUsage READ cpuUsage NOTIFY cpuUsageChanged)
    Q_PROPERTY(float lastCpuUsage READ lastCpuUsage NOTIFY lastCpuUsageChanged)
    Q_PROPERTY(float cpuClock READ cpuClock NOTIFY cpuClockChanged)
    Q_PROPERTY(int totalProcesses READ totalProcesses NOTIFY totalProcessesChanged)
    Q_PROPERTY(int totalThreads READ totalThreads NOTIFY totalThreadsChanged)

    Q_PROPERTY(QVariantMap gpuInfo READ gpuInfo NOTIFY gpuInfoChanged)

    Q_PROPERTY(QVariantMap memoryInfo READ memoryInfo NOTIFY memoryInfoChanged)

    Q_PROPERTY(QVariantMap networkInfo READ networkInfo NOTIFY networkInfoChanged)

    Q_PROPERTY(QVariantMap storageInfo READ storageInfo NOTIFY storageInfoChanged)
    

public:
    explicit ModelController(QObject *parent = nullptr);
    ~ModelController();

    float cpuTemp() const;
    QVariantList cpuUsage();
    float lastCpuUsage();
    float cpuClock() const;
    int totalProcesses() const;
    int totalThreads() const;

    QVariantMap gpuInfo() const;

    QVariantMap memoryInfo() const;

    QVariantMap networkInfo() const;

    QVariantMap storageInfo() const;

    CpuService m_cpuService;
    QThread cpuThread;
    CpuModel cpuModel;


signals:
    void cpuTempChanged();
    void cpuUsageChanged();
    void lastCpuUsageChanged();
    void cpuClockChanged();
    void totalProcessesChanged();
    void totalThreadsChanged();

    void gpuInfoChanged();

    void memoryInfoChanged();

    void networkInfoChanged();

    void storageInfoChanged();




public slots:
    void updateCpuInfo(); 

    void updateGpuInfo();

    void updateMemoryInfo();

    void updateNetworkInfo();

    void updateStorageInfo();

private:
    MemoryModel memoryModel;
    NetworkModel networkModel;
    StorageModel storageModel;
    GPUModel gpuModel;
    QTimer m_timer;




};

#endif // MODELCONTROLLER_H
