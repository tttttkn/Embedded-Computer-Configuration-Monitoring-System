#ifndef MEMORYSERVICE_H
#define MEMORYSERVICE_H

#include <QObject>
#include <QThread>
#include <QVariantMap>
#include <QDebug>
#include <sys/sysinfo.h>

struct MemoryInfo
{
    float usedMemory{};
    float availableMemory{};
    float ramUsage{};
    float swapUsed{};
    float swapAvailable{};
    float swapUsage{};
};
Q_DECLARE_METATYPE(MemoryInfo)

class MemoryService : public QObject
{
    Q_OBJECT
public:
    explicit MemoryService(QObject *parent = nullptr);
    ~MemoryService();

    void updateMemoryInfo();

public slots:
    void startMonitoring();
    void stopMonitoring();

signals:
    void memoryInfoUpdated(const MemoryInfo &info);

private:
    MemoryInfo m_memoryInfo;
    bool m_isMonitoring{false};
};

#endif // MEMORYSERVICE_H