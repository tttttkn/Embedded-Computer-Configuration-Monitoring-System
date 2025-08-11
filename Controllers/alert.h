// Alert.h
#ifndef ALERTMODEL_H
#define ALERTMODEL_H

#include <QAbstractListModel>
#include <QVector>
#include <QObject>

class Alert : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVariantMap newAlert READ newAlert NOTIFY newAlertChanged)
public:
    static Alert* getInstance();

    QVariantMap newAlert() const;

    static void addAlert(const QString &type, const QString &message);

    void startAlertCpuWarn(const float threshold, const float cpuUsage);
    void startAlertCpuCrit(const float threshold, const float cpuUsage);
    void startAlertRamWarn(const float threshold, const float ramUsage);

signals:
    void newAlertChanged();


public slots:




private:
    QVariantMap m_newAlert;

    void addAlertImpl(const QString &type, const QString &message);

    Alert(QObject* parent = nullptr) : QObject(parent) {}

    // Prevent copying
    Alert(const Alert&) = delete;
    Alert& operator=(const Alert&) = delete;


    bool m_isCpuWarn{false};
    bool m_isCpuCrit{false};
    bool m_isRamWarn{false};
};


#endif // ALERTMODEL_H