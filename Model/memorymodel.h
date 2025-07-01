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


public:
    explicit MemoryModel(QObject *parent = nullptr);

    QVariantMap getMemoryInfo() const { return m_memoryInfo; }

    void updateMemoryInfo();

    
    
signals:

public slots:


private:
    QVariantMap m_memoryInfo;

    QTimer m_timer;

};

#endif // MEMORYMODEL_H
