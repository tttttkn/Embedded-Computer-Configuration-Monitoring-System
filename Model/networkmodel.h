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


public:
    explicit NetworkModel(QObject *parent = nullptr);

    QVariantMap getNetworkInfo() const;

    void updateNetworkInfo();
    QString getWifiBand();
    void updateNetworkSpeed();

    
    
signals:

public slots:


private:
    float m_lastBytesReceived;
    float m_lastBytesTransmitted;
    QVariantMap m_networkInfo;
    QTimer m_timer;

};

#endif // NETWORKMODEL_H
