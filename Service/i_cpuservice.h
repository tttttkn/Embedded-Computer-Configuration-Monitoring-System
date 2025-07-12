#ifndef ICpuService_H
#define ICpuService_H

#include <QVariantList>
class ICpuService 
{
public:
    virtual ~ICpuService() {}



    virtual void updateCpuUsage() = 0;
    virtual void updateCpuTemperature() = 0;
    virtual void updateCpuClock() = 0;
    virtual void updateTotalProcesses() = 0;
    virtual void updateTotalThreads() = 0;

public slots:
    virtual void startMonitoring() = 0;
    virtual void stopMonitoring() = 0;

signals:

protected:
    // CpuInfo m_cpuInfo{};
};

#endif // ICpuService_H
