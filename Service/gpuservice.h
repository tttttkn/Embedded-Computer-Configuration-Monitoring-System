#ifndef GPUSERVICE_H
#define GPUSERVICE_H

#include <QObject>
#include <QThread>
#include <QVariantMap>
#include <QProcess>
#include <QDebug>

struct GpuInfo
{
    float gpuMemory{};
    float temperature{};
    float clockSpeedMax{};
    float clockSpeed{};
};
Q_DECLARE_METATYPE(GpuInfo)

class GpuService : public QObject
{
    Q_OBJECT
public:
    explicit GpuService(QObject *parent = nullptr);
    ~GpuService();

    void updateGpuInfo();

public slots:
    void startMonitoring();
    void stopMonitoring();

signals:
    void gpuInfoUpdated(const GpuInfo &info);

private:
    GpuInfo m_gpuInfo;
    bool m_isMonitoring{false};

    QString runCommand(const QString &cmd);
    float convertMemToFloat(const QString &str);
    float convertTempToFloat(const QString &str);
    float convertFreqToFloat(const QString &str);
};

#endif // GPUSERVICE_H