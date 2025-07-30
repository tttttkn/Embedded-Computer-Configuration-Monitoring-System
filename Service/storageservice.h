#ifndef STORAGESERVICE_H
#define STORAGESERVICE_H

#include <QObject>
#include <QThread>
#include <QVariantMap>
#include <QStorageInfo>
#include <QDebug>

struct StorageInfo
{
    double usedMB{};
    double totalMB{};
    double freeMB{};
};
Q_DECLARE_METATYPE(StorageInfo)

class StorageService : public QObject
{
    Q_OBJECT
public:
    explicit StorageService(QObject *parent = nullptr);
    ~StorageService();

    void updateStorageInfo();

public slots:
    void startMonitoring();
    void stopMonitoring();

signals:
    void storageInfoUpdated(const StorageInfo &info);

private:
    StorageInfo m_storageInfo;
    bool m_isMonitoring{false};
};

#endif // STORAGESERVICE_H