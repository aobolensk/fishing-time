#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include "config.h"
#include "mainwindow.h"

Config::Config(MainWindow *w) :
    window(w) {
    
}

void Config::deserialize(const QVariantMap &map) {
    if (isReady)
        return;
    window->activeLanguage = (Language)map["language"].toInt();
    isReady = true;
}

QByteArray Config::serialize() const {
    QJsonObject jsonObj;
    jsonObj["fishingtime_object"] = "config";
    jsonObj["language"] = (int)window->activeLanguage;
    QJsonDocument doc(jsonObj);
    return doc.toJson();
}
