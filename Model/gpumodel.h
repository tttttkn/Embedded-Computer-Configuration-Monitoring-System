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
class GPUModel : public QObject
{
    Q_OBJECT


public:
    explicit GPUModel(QObject *parent = nullptr);

    void updateGpuInfo();

    QVariantMap getGpuInfo() const { return m_gpuInfo; }

signals:

public slots:

private:
    QVariantMap m_gpuInfo;
    float convertMemToFloat(const QString &str);
    float convertTempToFloat(const QString &str);
    float convertFreqToFloat(const QString &str);

    QString runCommand(const QString &cmd);
};

#endif // GPUMODEL_H