#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include "config.h"

void Config::deserialize(const QVariantMap &map) {
    if (isReady)
        return;
    language = (Language)map["language"].toInt();
    isReady = true;
}

QByteArray Config::serialize() const {
    QJsonObject jsonObj;
    jsonObj["fishingtime_object"] = "config";
    jsonObj["language"] = (int)language;
    QJsonDocument doc(jsonObj);
    return doc.toJson();
}
