#ifndef NETWORKSERVICE_H
#define NETWORKSERVICE_H

#include <QObject>
#include <QThread>
#include <QVariantMap>
#include <QNetworkInterface>
#include <QNetworkConfigurationManager>
#include <QProcess>
#include <QFile>
#include <QDebug>
#include <QRegularExpression>

struct NetworkInfo
{
    QString ssid;
    QString interfaceName;
    QString ipv4;
    QString macAddress;
    QString wifiBand;
    float downloadSpeed{};
    float uploadSpeed{};
};
Q_DECLARE_METATYPE(NetworkInfo)

class NetworkService : public QObject
{
    Q_OBJECT
public:
    explicit NetworkService(QObject *parent = nullptr);
    ~NetworkService();

    void updateNetworkInfo();

public slots:
    void startMonitoring();
    void stopMonitoring();

signals:
    void networkInfoUpdated(const NetworkInfo &info);

private:
    NetworkInfo m_networkInfo;
    bool m_isMonitoring{false};
    float m_lastBytesReceived{0};
    float m_lastBytesTransmitted{0};

    QString getWifiBand(const QString &interfaceName);
    void updateNetworkSpeed(const QString &interfaceName);

    void parseIwOutput(const QString &output);

    QString executeCommand(const QString &program, const QStringList &arguments);

};

#endif // NETWORKSERVICE_H