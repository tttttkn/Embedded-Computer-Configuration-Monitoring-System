#include "networkmodel.h"

NetworkModel::NetworkModel(QObject *parent) : QObject(parent)
{
}


QVariantMap NetworkModel::getNetworkInfo() const
{
    return m_networkInfo;
}


void NetworkModel::updateNetworkInfo()
{
    QNetworkConfigurationManager manager;

    foreach (const QNetworkConfiguration &config, manager.allConfigurations()) {
        if (config.state() == QNetworkConfiguration::Active) {
            m_networkInfo["ssid"] = config.name(); 
            break;
        }
    }

    foreach (const QNetworkInterface &interface, QNetworkInterface::allInterfaces()) {
        if (interface.flags() & QNetworkInterface::IsUp &&
            !(interface.flags() & QNetworkInterface::IsLoopBack)) {
            foreach (const QNetworkAddressEntry &entry, interface.addressEntries()) {
                if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol) {
                    m_networkInfo["ipv4"] = entry.ip().toString();
                    m_networkInfo["interface"] = interface.name();
                    break;
                }
            }
        }
    }

    m_networkInfo["wifiBand"] = getWifiBand(); 
    m_networkInfo["macAddress"] = QNetworkInterface::interfaceFromName(m_networkInfo.value("interface").toString()).hardwareAddress();

    updateNetworkSpeed();



    qDebug() << "----------------------------------";
    qDebug() << "Network Info:";
    for (const QString &key : m_networkInfo.keys()) {
        qDebug() << key << ":" << m_networkInfo.value(key).toString();
    }

}

QString NetworkModel::getWifiBand() {
    QProcess process;
    process.start("iwconfig", QStringList() << "wlan0");
    process.waitForFinished();
    QString output = process.readAllStandardOutput();

    if (output.contains("Frequency:2.4")) {
        return "2.4";
    } else if (output.contains("Frequency:5")) {
        return "5";
    }
    return "TBD";
}

void NetworkModel::updateNetworkSpeed()
{
    QFile file("/proc/net/dev");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Cannot open /proc/net/dev";
        return;
    }

    QString content = file.readAll();
    file.close();

    QStringList lines = content.split('\n');
    for (const QString &line : lines) {
        if (line.contains("wlan0") || line.contains("enp0s3")) {
            QStringList parts = line.trimmed().split(QRegExp("\\s+"));
            if (parts.size() >= 10) {
                float bytesReceived = parts[1].toFloat();
                float bytesTransmitted = parts[9].toFloat();

                if (m_lastBytesReceived > 0) {
                    m_networkInfo["downloadSpeed"] = (bytesReceived - m_lastBytesReceived) / 1024.0 / 1024.0;
                    m_networkInfo["uploadSpeed"] = (bytesTransmitted - m_lastBytesTransmitted) / 1024.0 / 1024.0;

                m_lastBytesReceived = bytesReceived;
                m_lastBytesTransmitted = bytesTransmitted;
            }
            break;
            }
        }
    }
}
