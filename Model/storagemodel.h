#ifndef STORAGEMODEL_H
#define STORAGEMODEL_H

#include <QObject>
#include <QTimer>
#include <QProcess>
#include <QStorageInfo>
#include <QDebug>

class StorageModel : public QObject
{
    Q_OBJECT

public:
    explicit StorageModel(QObject *parent = nullptr);

    QVariantMap getStorageInfo() const;

signals:

public slots:

    void updateStorageInfo();

private:
    QVariantMap m_storageInfo;

};

#endif // STORAGEMODEL_H
