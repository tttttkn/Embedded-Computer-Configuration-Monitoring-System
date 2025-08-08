#include "networkmodel.h"

NetworkModel::NetworkModel(QObject *parent) : QObject(parent)
{
}

void NetworkModel::updateNetworkInfo(const NetworkInfo &info)
{
    m_networkInfo["ssid"] = info.ssid;
    m_networkInfo["interfaceName"] = info.interfaceName;
    m_networkInfo["ipv4"] = info.ipv4;
    m_networkInfo["macAddress"] = info.macAddress;
    m_networkInfo["wifiBand"] = info.wifiBand;
    m_networkInfo["downloadSpeed"] = info.downloadSpeed;
    m_networkInfo["uploadSpeed"] = info.uploadSpeed;


    // qDebug() << "SSID:" << info.ssid;
    // qDebug() << "Interface Name:" << info.interfaceName;
    // qDebug() << "IPv4:" << info.ipv4;
    // qDebug() << "MAC Address:" << info.macAddress;
    // qDebug() << "WiFi Band:" << info.wifiBand;
    // qDebug() << "Download Speed:" << info.downloadSpeed;
    // qDebug() << "Upload Speed:" << info.uploadSpeed;

    emit networkInfoUpdated();
}
