#ifndef STORAGEMODEL_H
#define STORAGEMODEL_H

#include <QObject>
#include <QVariantMap>
#include "Service/storageservice.h"

class StorageModel : public QObject
{
    Q_OBJECT

public:
    explicit StorageModel(QObject *parent = nullptr);

    QVariantMap getStorageInfo() const { return m_storageInfo; }

signals:

public slots:
    void updateStorageInfo(const StorageInfo &info);

private:
    QVariantMap m_storageInfo;
};

#endif // STORAGEMODEL_H
