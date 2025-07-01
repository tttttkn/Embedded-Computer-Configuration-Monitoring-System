#include "navigationcontroller.h"

NavigationController::NavigationController(QObject *parent) : QObject(parent)
{
}

void NavigationController::requestViewChange(const QString currentUrl, const QString targetUrl)
{
    qDebug() << "Current URL:" << currentUrl;
    qDebug() << "Target URL:" << targetUrl;
    if (currentUrl == targetUrl) {
        qDebug() << "No change in view.";
        return; // No change in view, do nothing
    }
    emit viewChanged(targetUrl);
}
