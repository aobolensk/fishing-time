#include "config.h"
#include "game.h"
#include "utils.h"

Config::Config() {

}

const QColor Config::LIGHT_THEME_WINDOW_COLOR = QColor(250, 250, 250);
const QColor Config::LIGHT_THEME_TEXT_COLOR = QColor(20, 20, 20);
const QColor Config::DARK_THEME_WINDOW_COLOR = QColor(64, 64, 64);
const QColor Config::DARK_THEME_TEXT_COLOR = QColor(240, 240, 240);

void Config::deserialize(Game *game, const QVariantMap &map) {
    if (isReady)
        return;
    game->activeLanguage = static_cast<Language>(map["language"].toInt());
    game->core.autoSavePeriod = map["autoSavePeriod"].toInt();
    game->inventoryType = static_cast<InventoryType>(map["inventoryType"].toInt());
    game->colorTheme = static_cast<ColorTheme>(map["colorTheme"].toInt());
    game->loggerLevel = static_cast<LoggerLevel>(map["loggerLevel"].toInt());
    if (map["logFile"].toString().size() > 0) {
        game->logFile = map["logFile"].toString();
    }
    if (map.constFind("showBgImages") != map.cend()) {
        game->showBgImages = static_cast<bool>(map["showBgImages"].toInt());
    }
    game->textFont.fromString(map["textFont"].toString());
    QVariantMap controls = map["controls"].toJsonObject().toVariantMap();
    game->controlsMenu.set(Controls::HIDE_UI_ELEMENTS, controls["hideUIElements"].toInt());
    game->controlsMenu.set(Controls::TOGGLE_FULLSCREEN_MODE, controls["toggleFullscreenMode"].toInt());
    game->controlsMenu.set(Controls::GO_TO_PREVIOUS_MENU, controls["goToPreviousMenu"].toInt());
    game->controlsMenu.set(Controls::EXIT_FROM_THE_GAME, controls["exitFromTheGame"].toInt());
    isReady = true;
}

QJsonObject Config::serialize(Game *game) const {
    QJsonObject jsonObj;
    jsonObj["fishingtime_object"] = "config";
    jsonObj["language"] = static_cast<int>(game->activeLanguage);
    jsonObj["autoSavePeriod"] = game->autoSavePeriod;
    jsonObj["inventoryType"] = static_cast<int>(game->inventoryType);
    jsonObj["colorTheme"] = static_cast<int>(game->colorTheme);
    jsonObj["loggerLevel"] = static_cast<int>(game->loggerLevel);
    jsonObj["logFile"] = game->logFile;
    jsonObj["showBgImages"] = static_cast<int>(game->showBgImages);
    jsonObj["textFont"] = game->font().toString();
    QVariantMap controls;
    controls["hideUIElements"] = game->controlsMenu.get(Controls::HIDE_UI_ELEMENTS)[0];
    controls["toggleFullscreenMode"] = game->controlsMenu.get(Controls::TOGGLE_FULLSCREEN_MODE)[0];
    controls["goToPreviousMenu"] = game->controlsMenu.get(Controls::GO_TO_PREVIOUS_MENU)[0];
    controls["exitFromTheGame"] = game->controlsMenu.get(Controls::EXIT_FROM_THE_GAME)[0];
    jsonObj["controls"] = QJsonObject::fromVariantMap(controls);
    return jsonObj;
}
