#include "storagemodel.h"


StorageModel::StorageModel(QObject *parent) : QObject(parent)
{
    connect(&m_timer, &QTimer::timeout, this, &StorageModel::updateStorageInfo);
    m_timer.start(5000);
    // Initialize storage info
    updateStorageInfo();
}


QVariantMap StorageModel::storageInfo() const
{
    return m_storageInfo;
}

void StorageModel::updateStorageInfo()
{
    m_storageInfo = getStorageInfo();
    emit storageInfoChanged();
}

QVariantMap StorageModel::getStorageInfo()
{
    QVariantMap info;

    qDebug() << "----------------------------------";
    qDebug() << "Storage Device Info:";
    
    foreach (const QStorageInfo &storage, QStorageInfo::mountedVolumes()) 
    {
        QByteArray device = storage.device();
        if (device.contains("sda") || device.contains("sdb")) {
            qDebug() << "Device:" << storage.device();
            qDebug() << "Mount point:" << storage.rootPath();
            qDebug() << "Total size:" << storage.bytesTotal()/1024/1024 << "MB";
            qDebug() << "Available:" << storage.bytesAvailable()/1024/1024 << "MB";
            qDebug() << "Usage:" << (1.0 - (double)storage.bytesAvailable()/storage.bytesTotal()) * 100 << "%";
            qDebug() << "File system:" << storage.fileSystemType();
            qDebug() << "----------------------------------";
        }
    }
    return info;
}

