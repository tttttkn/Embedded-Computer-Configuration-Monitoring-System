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
    Q_PROPERTY(QVariantMap storageInfo READ storageInfo NOTIFY storageInfoChanged)

public:
    explicit StorageModel(QObject *parent = nullptr);

    QVariantMap getStorageInfo();

    QVariantMap storageInfo() const;
signals:
    void storageInfoChanged();

public slots:

    void updateStorageInfo();

private:
    QVariantMap m_storageInfo;
    QTimer m_timer;

};

#endif // STORAGEMODEL_H
