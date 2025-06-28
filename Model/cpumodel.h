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
    Q_PROPERTY(float cpuTemp READ cpuTemp NOTIFY cpuTempChanged)
    Q_PROPERTY(QVariantList cpuUsage READ cpuUsage NOTIFY cpuUsageChanged)
    Q_PROPERTY(float lastCpuUsage READ lastCpuUsage NOTIFY lastCpuUsageChanged)
    Q_PROPERTY(float cpuClock READ cpuClock NOTIFY cpuClockChanged)
    Q_PROPERTY(int totalProcesses READ totalProcesses NOTIFY totalProcessesChanged)
    Q_PROPERTY(int totalThreads READ totalThreads NOTIFY totalThreadsChanged)

public:
    explicit CpuModel(QObject *parent = nullptr);
    ~CpuModel();

    float getCpuUsage() const;
    float getCpuTemperature() const;
    float getCpuClock() const;
    int getTotalProcesses() const;
    int getTotalThreads() const;



    float cpuTemp() const;
    QVariantList cpuUsage() const;
    float lastCpuUsage() const;
    float cpuClock() const;
    int totalProcesses() const;
    int totalThreads() const;

signals:
    void cpuTempChanged();
    void cpuUsageChanged();
    void lastCpuUsageChanged();
    void cpuClockChanged();
    void totalProcessesChanged();
    void totalThreadsChanged();

public slots:
    void updateCpuTemp();
    void updateCpuUsage();
    void updateCpuClock();
    void updateTotalProcesses();
    void updateTotalThreads();

private:
    QVariantList m_cpuUsage{};
    float m_cpuTemp{0.0F};
    float m_cpuClock{0.0F};
    int m_totalProcesses{0};
    int m_totalThreads{0};
    QTimer m_timer;




};

#endif // CPUMODEL_H
