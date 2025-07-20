#include "networkservice.h"

NetworkService::NetworkService(QObject *parent) : QObject(parent) {}
NetworkService::~NetworkService() { stopMonitoring(); }



QString NetworkService::executeCommand(const QString &program, const QStringList &arguments)
{
    QProcess process;
    process.start(program, arguments);
    process.waitForFinished();
    return process.readAllStandardOutput();
}

void NetworkService::parseIwOutput(const QString &output)
{
    QRegularExpression ssidRegex("SSID:\\s(.+)");
    QRegularExpression freqRegex("freq:\\s(\\d+)");
    QRegularExpression rxRateRegex("rx bitrate:\\s(\\d+\\.\\d+)");
    QRegularExpression txRateRegex("tx bitrate:\\s(\\d+\\.\\d+)");

    QRegularExpressionMatch ssidMatch = ssidRegex.match(output);
    if (ssidMatch.hasMatch()) {
        m_networkInfo.ssid = ssidMatch.captured(1).trimmed();
    }

    QRegularExpressionMatch freqMatch = freqRegex.match(output);
    if (freqMatch.hasMatch()) {
        int freq = freqMatch.captured(1).toInt();
        m_networkInfo.wifiBand = (freq >= 2400 && freq <= 2500) ? "2.4" : 
                                (freq >= 5000 && freq <= 6000) ? "5" : "Unknown";
    }


    QRegularExpressionMatch rxRateMatch = rxRateRegex.match(output);
    if (rxRateMatch.hasMatch()) {
        m_networkInfo.downloadSpeed = rxRateMatch.captured(1).toFloat() / 1024.0; // Convert to Mbps
    }

    QRegularExpressionMatch txRateMatch = txRateRegex.match(output);
    if (txRateMatch.hasMatch()) {
        m_networkInfo.uploadSpeed = txRateMatch.captured(1).toFloat() / 1024.0; // Convert to Mbps
    }
}

void NetworkService::updateNetworkInfo()
{
    QNetworkConfigurationManager manager;
    m_networkInfo.ssid.clear();
    for (const QNetworkConfiguration &config : manager.allConfigurations()) {
        if (config.state() == QNetworkConfiguration::Active) {
            m_networkInfo.interfaceName = config.name();
            break;
        }
    }

    for (const QNetworkInterface &interface : QNetworkInterface::allInterfaces()) {
        if (interface.flags() & QNetworkInterface::IsUp &&
            !(interface.flags() & QNetworkInterface::IsLoopBack)) {
            for (const QNetworkAddressEntry &entry : interface.addressEntries()) {
                if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol) {
                    m_networkInfo.ipv4 = entry.ip().toString();
                    break;
                }
            }
            break;
        }
    }

    if (m_networkInfo.interfaceName.isEmpty()) {
        qWarning() << "No active network interface found.";
        return;
    }

    QString iwOutput = executeCommand("iw", {"dev", m_networkInfo.interfaceName, "link"});

    parseIwOutput(iwOutput);


}

// QString NetworkService::getWifiBand(const QString &interfaceName)
// {
//     QProcess process;
//     process.start("iwconfig", QStringList() << interfaceName);
//     process.waitForFinished();
//     QString output = process.readAllStandardOutput();

//     if (output.contains("Frequency:2.4")) {
//         return "2.4";
//     } else if (output.contains("Frequency:5")) {
//         return "5";
//     }
//     return "None";
// }

// void NetworkService::updateNetworkSpeed(const QString &interfaceName)
// {
//     QFile file("/proc/net/dev");
//     if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//         qWarning() << "Cannot open /proc/net/dev";
//         return;
//     }

//     QString content = file.readAll();
//     file.close();

//     QStringList lines = content.split('\n');
//     for (const QString &line : lines) {
//         if (line.contains(interfaceName)) {
//             QStringList parts = line.trimmed().split(QRegExp("\\s+"));
//             if (parts.size() >= 10) {
//                 float bytesReceived = parts[1].toFloat();
//                 float bytesTransmitted = parts[9].toFloat();

//                 if (m_lastBytesReceived > 0) {
//                     m_networkInfo.downloadSpeed = (bytesReceived - m_lastBytesReceived) / 1024.0 / 1024.0;
//                     m_networkInfo.uploadSpeed = (bytesTransmitted - m_lastBytesTransmitted) / 1024.0 / 1024.0;
//                 }
//                 m_lastBytesReceived = bytesReceived;
//                 m_lastBytesTransmitted = bytesTransmitted;
//             }
//             break;
//         }
//     }
// }

void NetworkService::startMonitoring()
{
    m_isMonitoring = true;
    // qDebug() << "Starting Network monitoring...";
    while (m_isMonitoring) {
        updateNetworkInfo();
        emit networkInfoUpdated(m_networkInfo);
        QThread::sleep(1);
    }
}

void NetworkService::stopMonitoring()
{
    m_isMonitoring = false;
    // qDebug() << "Network monitoring stopped.";
}