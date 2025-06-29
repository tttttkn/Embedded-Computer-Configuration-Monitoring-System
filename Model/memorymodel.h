#ifndef MEMORYMODEL_H
#define MEMORYMODEL_H

#include <QObject>
#include <QTimer>
#include <QVariant>
#include <QDebug>
#include <sys/sysinfo.h>

class MemoryModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariantMap memoryInfo READ memoryInfo NOTIFY memoryInfoChanged)

public:
    explicit MemoryModel(QObject *parent = nullptr);

    void getMemoryInfo();

    
    
    QVariantMap memoryInfo() const;
signals:
    void memoryInfoChanged();

public slots:

    void updateMemoryInfo();

private:
    QVariantMap m_memoryInfo;
    QTimer m_timer;

};

#endif // MEMORYMODEL_H
