#ifndef CPUMODEL_H
#define CPUMODEL_H

//#include <QDeclarativeItem>
#include <QObject>
#include <QQuickItem>
#include <vector>
#include <QTimer>

class CpuModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float cpuTemp READ cpuTemp NOTIFY cpuTempChanged)
    Q_PROPERTY(float cpuUsage READ cpuUsage NOTIFY cpuUsageChanged)



public:
    explicit CpuModel(QObject *parent = nullptr);

    float getCurentCpuUsage() const;
    float cpuTemp() const;
    float cpuUsage() const;

signals:
    void cpuTempChanged();
    void cpuUsageChanged();

public slots:
    void updateCpuTemp();
    void updateCpuUsage();



private:
    float m_cpuUsage;
    float m_cpuTemp;
    QTimer m_timer;




};

#endif // CPUMODEL_H
