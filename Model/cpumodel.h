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

class CpuModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float cpuTemp READ cpuTemp NOTIFY cpuTempChanged)
    Q_PROPERTY(float cpuUsage READ cpuUsage NOTIFY cpuUsageChanged)
    Q_PROPERTY(float cpuClock READ cpuClock NOTIFY cpuClockChanged)
    Q_PROPERTY(int totalProcesses READ totalProcesses NOTIFY totalProcessesChanged)
    Q_PROPERTY(int totalThreads READ totalThreads NOTIFY totalThreadsChanged)

public:
    explicit CpuModel(QObject *parent = nullptr);
    ~CpuModel();

    float getCurrentCpuUsage() const;
    float getCpuTemperature() const;
    float getCpuClock() const;
    int getTotalProcesses() const;
    int getTotalThreads() const;



    float cpuTemp() const;
    float cpuUsage() const;
    float cpuClock() const;
    int totalProcesses() const;
    int totalThreads() const;

signals:
    void cpuTempChanged();
    void cpuUsageChanged();
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
    float m_cpuUsage{0.0F};
    float m_cpuTemp{0.0F};
    float m_cpuClock{0.0F};
    int m_totalProcesses{0};
    int m_totalThreads{0};
    QTimer m_timer;




};

#endif // CPUMODEL_H
