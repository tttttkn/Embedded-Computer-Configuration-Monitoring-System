#include "storagemodel.h"


StorageModel::StorageModel(QObject *parent) : QObject(parent)
{
}


void StorageModel::updateStorageInfo(const StorageInfo &info)
{
    m_storageInfo["usedMB"] = info.usedMB;
    m_storageInfo["totalMB"] = info.totalMB;
    m_storageInfo["freeMB"] = info.freeMB;
}

