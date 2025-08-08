#ifndef MODELCONTROLLER_H
#define MODELCONTROLLER_H

#include <QObject>
#include <QDebug>
#include "Model/cpumodel.h"
#include "Model/memorymodel.h"
#include "Model/networkmodel.h"
#include "Model/storagemodel.h"
#include "Model/gpumodel.h"
#include "Model/systemmodel.h"
#include "logger.h"


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

    Q_PROPERTY(QVariantMap staticSystemInfo READ staticSystemInfo NOTIFY staticSystemInfoChanged)

    Q_PROPERTY(QString uptime READ uptime NOTIFY uptimeChanged)



public:
    explicit ModelController(QObject *parent = nullptr);
    ~ModelController();

    void initServices();

    float cpuTemp() const;
    QVariantList cpuUsage() const;
    float lastCpuUsage() const;
    float cpuClock() const;
    int totalProcesses() const;
    int totalThreads() const;

    QVariantMap gpuInfo() const;

    QVariantMap memoryInfo() const;

    QVariantMap networkInfo() const;

    QVariantMap storageInfo() const;

    QVariantMap staticSystemInfo() const;

    QString uptime() const;



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

    void staticSystemInfoChanged();

    void uptimeChanged();


public slots:
    void updateCpuInfo(); 

    void updateGpuInfo();

    void updateMemoryInfo();

    void updateNetworkInfo();

    void updateStorageInfo();

    void updateStaticSystemInfo();

    void updateSystemInfo();


private:
    CpuModel cpuModel;
    MemoryModel memoryModel;
    NetworkModel networkModel;
    StorageModel storageModel;
    GPUModel gpuModel;
    SystemModel systemModel;

    CpuService m_cpuService;
    QThread cpuThread;

    GpuService m_gpuService;
    QThread gpuThread;

    MemoryService m_memoryService;
    QThread memoryThread;

    NetworkService m_networkService;
    QThread networkThread;

    StorageService m_storageService;
    QThread storageThread;

    SystemService m_systemService;
    QThread systemThread;

};

#endif // MODELCONTROLLER_H
