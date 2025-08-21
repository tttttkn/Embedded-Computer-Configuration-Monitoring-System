#include "systemmodel.h"

SystemModel::SystemModel(QObject *parent)
    : QObject(parent)
{
}

void SystemModel::updateStaticSystemInfo(const StaticSystemInfo &info)
{
    m_staticSystemInfo["hostname"] = info.hostname;
    m_staticSystemInfo["os"] = info.os;
    m_staticSystemInfo["kernelVersion"] = info.kernelVersion;

    emit staticSystemInfoUpdated();
}

void SystemModel::updateSystemInfo(const QString uptime)
{
    m_uptime = uptime;
    emit systemInfoUpdated();
}

void SystemModel::setCpuWarn(int value)
{
    if (m_cpuWarn != value) {
        m_cpuWarn = value;
        saveConfig();
    }
    Logger::addLog(QString("CPU warning level set to %1 %").arg(value));
}

void SystemModel::setCpuCrit(int value)
{
    if (m_cpuCrit != value) {
        m_cpuCrit = value;
        saveConfig();
    }
    Logger::addLog(QString("CPU critical level set to %1 %").arg(value));
}

void SystemModel::setRamWarn(int value)
{
    if (m_ramWarn != value) {
        m_ramWarn = value;
        saveConfig();
    }
    Logger::addLog(QString("RAM warning level set to %1 %").arg(value));
}

void SystemModel::loadConfig()
{
    QFile file(CONFIG_PATH);
    if (!file.open(QIODevice::ReadOnly)) 
    {
        Logger::addLog(QString("Failed to open config file: %1").arg(file.errorString()));
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject()) 
    {
        Logger::addLog("Invalid JSON format");
        return;
    }

    QJsonObject obj = doc.object();

    m_cpuWarn = obj.value("cpuWarn").toInt();
    m_cpuCrit = obj.value("cpuCrit").toInt();
    m_ramWarn = obj.value("ramWarn").toInt();

    qDebug() << "Loaded config:";
    qDebug() << "CPU Warning Level:" << m_cpuWarn;
    qDebug() << "CPU Critical Level:" << m_cpuCrit;
    qDebug() << "RAM Warning Level:" << m_ramWarn;
}

void SystemModel::init()
{
    // Load configuration from JSON file
    loadConfig();

    qDebug() << "System model initialized";
}

void SystemModel::saveConfig()
{
    QFile file(CONFIG_PATH);
    if (!file.open(QIODevice::WriteOnly)) {
        Logger::addLog(QString("Failed to open config file for writing: %1").arg(file.errorString()));
        return;
    }

    QJsonObject obj;
    obj["cpuWarn"] = m_cpuWarn;
    obj["cpuCrit"] = m_cpuCrit;
    obj["ramWarn"] = m_ramWarn;

    QJsonDocument doc(obj);
    file.write(doc.toJson());
    file.close();
}
