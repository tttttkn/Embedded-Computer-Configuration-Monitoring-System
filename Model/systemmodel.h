#ifndef SYSTEMMODEL_H
#define SYSTEMMODEL_H

#include <QObject>
#include <QVariantMap>
#include "Service/systemservice.h"
#include "../Controllers/logger.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <string>

#define CONFIG_PATH "/usr/share/monitor/config.json"

class SystemModel : public QObject
{
    Q_OBJECT


public:
    explicit SystemModel(QObject *parent = nullptr);

    QVariantMap getStaticSystemInfo() const { return m_staticSystemInfo; }

    QString getUptime() const { return m_uptime; }

    void setCpuWarn(int value);
    void setCpuCrit(int value);
    void setRamWarn(int value);

    void init();

    
    signals:
    void staticSystemInfoUpdated();
    void systemInfoUpdated();
    
    public slots:
    void updateStaticSystemInfo(const StaticSystemInfo &info);
    void updateSystemInfo(const QString uptime);
    int getCpuWarn() const { return m_cpuWarn; }
    int getCpuCrit() const { return m_cpuCrit; }
    int getRamWarn() const { return m_ramWarn; }
    
private:
    QVariantMap m_staticSystemInfo;
    QString m_uptime;
    
    int m_cpuWarn{0};
    int m_cpuCrit{0};
    int m_ramWarn{0};

    void loadConfig();
    void saveConfig();

};

#endif // SYSTEMMODEL_H
