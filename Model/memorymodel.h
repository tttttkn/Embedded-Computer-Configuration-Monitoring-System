#ifndef MEMORYMODEL_H
#define MEMORYMODEL_H

#include <QObject>
#include <QVariantMap>
#include "Service/memoryservice.h"

class MemoryModel : public QObject
{
    Q_OBJECT

public:
    explicit MemoryModel(QObject *parent = nullptr);

    QVariantMap getMemoryInfo() const { return m_memoryInfo; }

signals:

public slots:
    void updateMemoryInfo(const MemoryInfo &info);

private:
    QVariantMap m_memoryInfo;
};

#endif // MEMORYMODEL_H
