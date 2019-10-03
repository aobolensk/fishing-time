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
    game->inventoryType = (InventoryType)map["inventoryType"].toInt();
    game->colorTheme = (ColorTheme)map["colorTheme"].toInt();
    game->textFont.fromString(map["textFont"].toString());
    isReady = true;
}

QJsonObject Config::serialize() const {
    QJsonObject jsonObj;
    jsonObj["fishingtime_object"] = "config";
    jsonObj["language"] = (int)game->activeLanguage;
    jsonObj["autoSavePeriod"] = game->autoSavePeriod;
    jsonObj["inventoryType"] = (int)game->inventoryType;
    jsonObj["colorTheme"] = (int)game->colorTheme;
    jsonObj["textFont"] = game->font().toString();
    return jsonObj;
}

void Config::applyColorTheme(ColorTheme theme) {
    qDebug() << "Applied theme:" << (int)theme;
}
