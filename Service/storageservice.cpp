#include "storageservice.h"

StorageService::StorageService(QObject *parent) : QObject(parent) {}
StorageService::~StorageService() { stopMonitoring(); }

void StorageService::updateStorageInfo()
{
    QStorageInfo root = QStorageInfo::root();
    if (!root.isValid() || !root.isReady()) {
        qWarning() << "Storage root is not valid or not ready.";
        return;
    }

    qint64 usedBytes = root.bytesTotal() - root.bytesFree();
    qint64 totalBytes = root.bytesTotal();

    m_storageInfo.usedMB = usedBytes / (1024.0 * 1024);
    m_storageInfo.totalMB = totalBytes / (1024.0 * 1024);
    m_storageInfo.freeMB = root.bytesFree() / (1024.0 * 1024);
}

void StorageService::startMonitoring()
{
    m_isMonitoring = true;
    qDebug() << "Starting Storage monitoring...";
    while (m_isMonitoring) {
        updateStorageInfo();
        emit storageInfoUpdated(m_storageInfo);
        QThread::sleep(1);
    }
}

void StorageService::stopMonitoring()
{
    m_isMonitoring = false;
    qDebug() << "Storage monitoring stopped.";
}