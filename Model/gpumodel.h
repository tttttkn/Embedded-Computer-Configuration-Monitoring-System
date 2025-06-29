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

    Q_PROPERTY(QVariantMap gpuInfo READ gpuInfo NOTIFY gpuInfoChanged)

public:
    explicit GPUModel(QObject *parent = nullptr);

    QVariantMap gpuInfo() const;

signals:
    void gpuInfoChanged();

public slots:
    void updateGpuInfo();

private:
    QVariantMap m_gpuInfo;
    QTimer m_timer;

    QString runCommand(const QString &cmd);
};

#endif // GPUMODEL_H