#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QString>

class Logger : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString newLog READ newLog NOTIFY newLogChanged)

public:
    static Logger* getInstance();

    static void addLog(const QString &log);

    QString newLog() const { return m_newLog; }

signals:
    void newLogChanged();

private:
    void addLogImpl(const QString &log);

    QString m_newLog;
    Logger(QObject* parent = nullptr) : QObject(parent) {}
    
    // Prevent copying
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
};

#endif // LOGGER_H
