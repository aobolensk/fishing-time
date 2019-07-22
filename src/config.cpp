#include <QDebug>
#include "config.h"
#include "game.h"

Config::Config(Game *game) :
    game(game) {
    
}

void Config::deserialize(const QVariantMap &map) {
    if (isReady)
        return;
    game->activeLanguage = (Language)map["language"].toInt();
    game->autoSavePeriod = map["autoSavePeriod"].toInt();
    isReady = true;
}

QJsonObject Config::serialize() const {
    QJsonObject jsonObj;
    jsonObj["fishingtime_object"] = "config";
    jsonObj["language"] = (int)game->activeLanguage;
    jsonObj["autoSavePeriod"] = game->autoSavePeriod;
    return jsonObj;
}
