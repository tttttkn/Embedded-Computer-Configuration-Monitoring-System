#include "logger.h"

Logger* Logger::getInstance()
{
    static Logger instance; // Singleton instance
    return &instance;
}

void Logger::addLog(const QString &log)
{
    getInstance()->addLogImpl(log);
}

void Logger::addLogImpl(const QString &log)
{
    m_newLog = log;
    emit newLogChanged();
}