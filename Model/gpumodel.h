#ifndef GPUMODEL_H
#define GPUMODEL_H

#include <QObject>
#include <QTimer>
#include <QVariantMap>
#include <QProcess>
#include <QDebug>

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
    QTimer m_timer;

    QString runCommand(const QString &cmd);
};

#endif // GPUMODEL_H