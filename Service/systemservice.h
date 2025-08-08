#ifndef SYSTEMSERVICE_H
#define SYSTEMSERVICE_H

#include <QObject>
#include <QThread>
#include <QVariantMap>
#include <QDebug>
#include <QHostInfo>
#include <QSysInfo>

struct StaticSystemInfo {
    QString hostname{};
    QString os{};
    QString kernelVersion{};
};


Q_DECLARE_METATYPE(StaticSystemInfo)

class SystemService : public QObject
{
    Q_OBJECT
public:
    explicit SystemService(QObject *parent = nullptr);
    ~SystemService();

    void calculateUptime();

    // void updateSystemInfo();

public slots:
    void init();
    void startMonitoring();
    void stopMonitoring();
    
signals:
    void staticSystemInfoUpdated(const StaticSystemInfo &info);
    void systemInfoUpdated(const QString uptime);
    // void systemInfoUpdated(const SystemInfo &info);

private:
    StaticSystemInfo m_staticSystemInfo;
    QString m_uptime;
    bool m_isMonitoring{false};
};

#endif // SYSTEMSERVICE_H