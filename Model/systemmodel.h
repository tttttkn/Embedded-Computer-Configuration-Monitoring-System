#ifndef SYSTEMMODEL_H
#define SYSTEMMODEL_H

#include <QObject>
#include <QVariantMap>
#include "Service/systemservice.h"

class SystemModel : public QObject
{
    Q_OBJECT

public:
    explicit SystemModel(QObject *parent = nullptr);

    QVariantMap getStaticSystemInfo() const { return m_staticSystemInfo; }

    QString getUptime() const { return m_uptime; }

signals:
    void staticSystemInfoUpdated();
    void systemInfoUpdated();

public slots:
    void updateStaticSystemInfo(const StaticSystemInfo &info);
    void updateSystemInfo(const QString uptime);

private:
    QVariantMap m_staticSystemInfo;
    QString m_uptime;

};

#endif // SYSTEMMODEL_H
