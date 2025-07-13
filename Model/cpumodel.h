#ifndef CPUMODEL_H
#define CPUMODEL_H

//#include <QDeclarativeItem>
#include <QObject>
#include <QQuickItem>
#include <QTimer>
#include "Service/cpuservice.h"


class CpuModel : public QObject
{
    Q_OBJECT


public:
    explicit CpuModel(QObject *parent = nullptr);
    ~CpuModel();




    QVariantList getCpuUsage() const { return m_cpuUsage; }
    float getCpuTemperature() const { return m_cpuTemp; }
    float getCpuClock() const { return m_cpuClock; }
    int getTotalProcesses() const { return m_totalProcesses; }
    int getTotalThreads() const { return m_totalThreads; }


public slots:
    void updateCpuInfo(const CpuInfo &info);



signals:




private:
    QVariantList m_cpuUsage{};
    float m_cpuTemp{0.0F};
    float m_cpuClock{0.0F};
    int m_totalProcesses{0};
    int m_totalThreads{0};




};

#endif // CPUMODEL_H
