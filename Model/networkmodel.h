#ifndef NETWORKMODEL_H
#define NETWORKMODEL_H

#include <QObject>
#include <QVariantMap>
#include "Service/networkservice.h"

class NetworkModel : public QObject
{
    Q_OBJECT

public:
    explicit NetworkModel(QObject *parent = nullptr);

    QVariantMap getNetworkInfo() const { return m_networkInfo; }

signals:

public slots:
    void updateNetworkInfo(const NetworkInfo &info);

private:
    QVariantMap m_networkInfo;
};

#endif // NETWORKMODEL_H
