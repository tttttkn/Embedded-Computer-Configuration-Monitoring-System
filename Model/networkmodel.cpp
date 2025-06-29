#include "networkmodel.h"

NetworkModel::NetworkModel(QObject *parent) : QObject(parent)
{
    connect(&m_timer, &QTimer::timeout, this, &NetworkModel::updateNetworkInfo);
    m_timer.start(5000);
    updateNetworkInfo();
}


QVariantMap NetworkModel::networkInfo() const
{
    return m_networkInfo;
}

void NetworkModel::updateNetworkInfo()
{
    getNetworkInfo();
    emit networkInfoChanged();
}

void NetworkModel::getNetworkInfo()
{
    QNetworkConfigurationManager manager;

    // Lấy cấu hình mạng đang hoạt động
    foreach (const QNetworkConfiguration &config, manager.allConfigurations()) {
        if (config.state() == QNetworkConfiguration::Active) {
            m_networkInfo["ssid"] = config.name(); // SSID (nếu là WiFi)
            break;
        }
    }

    // Lấy IPv4 từ giao diện mạng
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

    m_networkInfo["wifiBand"] = getWifiBand(); // Lấy băng tần WiFi
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
    return "Unknown";
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

    // Tìm dòng chứa wlan0 hoặc enp0s3
    QStringList lines = content.split('\n');
    for (const QString &line : lines) {
        if (line.contains("wlan0") || line.contains("enp0s3")) {
            QStringList parts = line.trimmed().split(QRegExp("\\s+"));
            if (parts.size() >= 10) {
                float bytesReceived = parts[1].toFloat();
                float bytesTransmitted = parts[9].toFloat();

                // Tính tốc độ (KB/s)
                if (m_lastBytesReceived > 0) {
                    m_networkInfo["downloadSpeed"] = (bytesReceived - m_lastBytesReceived) / 1024.0;
                    m_networkInfo["uploadSpeed"] = (bytesTransmitted - m_lastBytesTransmitted) / 1024.0;

                m_lastBytesReceived = bytesReceived;
                m_lastBytesTransmitted = bytesTransmitted;
            }
            break;
            }
        }
    }
}
