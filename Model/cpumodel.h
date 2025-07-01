#ifndef CPUMODEL_H
#define CPUMODEL_H

//#include <QDeclarativeItem>
#include <QObject>
#include <QQuickItem>
#include <QTimer>
#include <QDebug>
#include <QProcess>

#include <statgrab.h>
#include <cpufreq.h>

#define MAX_DATA_POINTS 20 // Số điểm dữ liệu tối đa cho biểu đồ

class CpuModel : public QObject
{
    Q_OBJECT


public:
    explicit CpuModel(QObject *parent = nullptr);
    ~CpuModel();

    void updateCpuUsage();
    void updateCpuTemperature();
    void updateCpuClock();
    void updateTotalProcesses();
    void updateTotalThreads();

    QVariantList getCpuUsage() const { return m_cpuUsage; }
    float getCpuTemperature() const { return m_cpuTemp; }
    float getCpuClock() const { return m_cpuClock; }
    int getTotalProcesses() const { return m_totalProcesses; }
    int getTotalThreads() const { return m_totalThreads; }





signals:




private:
    QVariantList m_cpuUsage{};
    float m_cpuTemp{0.0F};
    float m_cpuClock{0.0F};
    int m_totalProcesses{0};
    int m_totalThreads{0};




};

#endif // CPUMODEL_H
