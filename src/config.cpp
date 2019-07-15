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
    window->autoSavePeriod = map["autoSavePeriod"].toInt();
    isReady = true;
}

QByteArray Config::serialize() const {
    QJsonObject jsonObj;
    jsonObj["fishingtime_object"] = "config";
    jsonObj["language"] = (int)window->activeLanguage;
    jsonObj["autoSavePeriod"] = window->autoSavePeriod;
    QJsonDocument doc(jsonObj);
    return doc.toJson();
}
