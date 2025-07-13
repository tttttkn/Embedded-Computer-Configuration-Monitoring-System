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
}
