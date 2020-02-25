#include "config.h"
#include "game.h"
#include "utils.h"

Config::Config(Core *core) :
    core(core) {

}

const QColor Config::LIGHT_THEME_WINDOW_COLOR = QColor(250, 250, 250);
const QColor Config::LIGHT_THEME_TEXT_COLOR = QColor(20, 20, 20);
const QColor Config::DARK_THEME_WINDOW_COLOR = QColor(64, 64, 64);
const QColor Config::DARK_THEME_TEXT_COLOR = QColor(240, 240, 240);

void Config::deserialize(const QVariantMap &map) {
    if (isReady)
        return;
    core->activeLanguage = static_cast<Language>(map["language"].toInt());
    core->autoSavePeriod = map["autoSavePeriod"].toInt();
    core->inventoryType = static_cast<InventoryType>(map["inventoryType"].toInt());
    core->colorTheme = static_cast<ColorTheme>(map["colorTheme"].toInt());
    core->loggerLevel = static_cast<LoggerLevel>(map["loggerLevel"].toInt());
    if (map["logFile"].toString().size() > 0) {
        core->logFile = map["logFile"].toString();
    }
    if (map.constFind("showBgImages") != map.cend()) {
        core->showBgImages = static_cast<bool>(map["showBgImages"].toInt());
    }
    core->textFont.fromString(map["textFont"].toString());
    QVariantMap controlsMap = map["controls"].toJsonObject().toVariantMap();
    this->setKey(Controls::HIDE_UI_ELEMENTS, controlsMap["hideUIElements"].toInt());
    this->setKey(Controls::TOGGLE_FULLSCREEN_MODE, controlsMap["toggleFullscreenMode"].toInt());
    this->setKey(Controls::GO_TO_PREVIOUS_MENU, controlsMap["goToPreviousMenu"].toInt());
    this->setKey(Controls::EXIT_FROM_THE_GAME, controlsMap["exitFromTheGame"].toInt());
    isReady = true;
}

QJsonObject Config::serialize() const {
    QJsonObject jsonObj;
    jsonObj["fishingtime_object"] = "config";
    jsonObj["language"] = static_cast<int>(core->activeLanguage);
    jsonObj["autoSavePeriod"] = core->autoSavePeriod;
    jsonObj["inventoryType"] = static_cast<int>(core->inventoryType);
    jsonObj["colorTheme"] = static_cast<int>(core->colorTheme);
    jsonObj["loggerLevel"] = static_cast<int>(core->loggerLevel);
    jsonObj["logFile"] = core->logFile;
    jsonObj["showBgImages"] = static_cast<int>(core->showBgImages);
    jsonObj["textFont"] = core->textFont.toString();
    QVariantMap controlsMap;
    controlsMap["hideUIElements"] = this->getKey(Controls::HIDE_UI_ELEMENTS)[0];
    controlsMap["toggleFullscreenMode"] = this->getKey(Controls::TOGGLE_FULLSCREEN_MODE)[0];
    controlsMap["goToPreviousMenu"] = this->getKey(Controls::GO_TO_PREVIOUS_MENU)[0];
    controlsMap["exitFromTheGame"] = this->getKey(Controls::EXIT_FROM_THE_GAME)[0];
    jsonObj["controls"] = QJsonObject::fromVariantMap(controlsMap);
    return jsonObj;
}

QKeySequence Config::getKey(Controls control) const {
    return this->controls[static_cast<size_t>(control)];
}

void Config::setDefaultKey(Controls control, int key) {
    this->defaultControls[static_cast<size_t>(control)] = QKeySequence(key);
}

void Config::setKey(Controls control, int key) {
    this->controls[static_cast<size_t>(control)] = QKeySequence(key);
}
