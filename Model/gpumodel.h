#ifndef GPUMODEL_H
#define GPUMODEL_H

#include <QObject>
#include <QTimer>
#include <QVariantMap>
#include <QProcess>
#include <QDebug>
#include <sys/sysinfo.h>
#include <QQuickItem>
#include <QFile>
#include "Service/gpuservice.h"



class GPUModel : public QObject
{
    Q_OBJECT


public:
    explicit GPUModel(QObject *parent = nullptr);

    
    QVariantMap getGpuInfo() const { return m_gpuInfo; }
    
    signals:
    
    public slots:
    void updateGpuInfo(const GpuInfo &info);

private:
    QVariantMap m_gpuInfo;

};

#endif // GPUMODEL_H