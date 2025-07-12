#include "storagemodel.h"


StorageModel::StorageModel(QObject *parent) : QObject(parent)
{
}


QVariantMap StorageModel::getStorageInfo() const
{
    return m_storageInfo;
}


void StorageModel::updateStorageInfo()
{
    QVariantMap info;

    qDebug() << "----------------------------------";
    qDebug() << "Storage Device Info:";
    
    QStorageInfo root = QStorageInfo::root();

    if (!root.isValid() || !root.isReady()) {
        qWarning() << "Không thể đọc thông tin phân vùng root!";
        return;
    }

    qint64 usedBytes = root.bytesTotal() - root.bytesFree();
    qint64 totalBytes = root.bytesTotal();

    double usedMB = usedBytes / (1024.0 * 1024);
    double totalMB = totalBytes / (1024.0 * 1024);

    info["usedMB"] = usedMB;
    info["totalMB"] = totalMB;
    info["freeMB"] = root.bytesFree() / (1024.0 * 1024);

    m_storageInfo = info;
}

