#ifndef NETWORKMODEL_H
#define NETWORKMODEL_H

#include <QObject>
#include <QTimer>
#include <QNetworkInterface>
#include <QNetworkConfigurationManager>
#include <QNetworkConfiguration>
#include <QProcess>
#include <QDebug>
#include <QFile>

class NetworkModel : public QObject
{
 Q_OBJECT

    Q_PROPERTY(QVariantMap networkInfo READ networkInfo NOTIFY networkInfoChanged)

public:
    explicit NetworkModel(QObject *parent = nullptr);

    void getNetworkInfo();
    QString getWifiBand();
    void updateNetworkSpeed();

    
    
    QVariantMap networkInfo() const;
signals:
    void networkInfoChanged();

public slots:

    void updateNetworkInfo();

private:
    float m_lastBytesReceived;
    float m_lastBytesTransmitted;
    QVariantMap m_networkInfo;
    QTimer m_timer;

};

#endif // NETWORKMODEL_H
