// AlertModel.h
#ifndef ALERTMODEL_H
#define ALERTMODEL_H

#include <QAbstractListModel>
#include <QVector>
#include <QObject>

class AlertModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVariantMap newAlert READ newAlert NOTIFY newAlertChanged)
public:
    static AlertModel* getInstance();

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

    AlertModel(QObject* parent = nullptr) : QObject(parent) {}

    // Prevent copying
    AlertModel(const AlertModel&) = delete;
    AlertModel& operator=(const AlertModel&) = delete;


    bool m_isCpuWarn{false};
    bool m_isCpuCrit{false};
    bool m_isRamWarn{false};
};


#endif // ALERTMODEL_H