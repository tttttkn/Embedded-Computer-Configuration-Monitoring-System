#ifndef NAVIGATIONCONTROLLER_H
#define NAVIGATIONCONTROLLER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QDebug>

class NavigationController : public QObject
{
    Q_OBJECT
public:
    explicit NavigationController(QObject *parent = nullptr);

    Q_INVOKABLE void requestViewChange(const QString currentUrl, const QString targetUrl);

signals:
    void viewChanged(const QString targetUrl);


private:

};

#endif // NAVIGATIONCONTROLLER_H
