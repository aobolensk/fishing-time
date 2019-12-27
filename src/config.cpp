#include <QApplication>
#include <QStyleFactory>
#include "config.h"
#include "game.h"
#include "utils.h"

Config::Config(Game *game) :
        game(game) {
    qDebug() << "Project directory:" << TOSTRING(PROJECT_DIR);
}

const QString Config::imagesDirectory = TOSTRING(PROJECT_DIR) "/images/";
const QColor Config::LIGHT_THEME_WINDOW_COLOR = QColor(250, 250, 250);
const QColor Config::LIGHT_THEME_TEXT_COLOR = QColor(20, 20, 20);
const QColor Config::DARK_THEME_WINDOW_COLOR = QColor(64, 64, 64);
const QColor Config::DARK_THEME_TEXT_COLOR = QColor(240, 240, 240);

void Config::deserialize(const QVariantMap &map) {
    if (isReady)
        return;
    game->activeLanguage = (Language)map["language"].toInt();
    game->autoSavePeriod = map["autoSavePeriod"].toInt();
    game->inventoryType = (InventoryType)map["inventoryType"].toInt();
    game->colorTheme = (ColorTheme)map["colorTheme"].toInt();
    game->loggerLevel = (LoggerLevel)map["loggerLevel"].toInt();
    if (map["logFile"].toString().size() > 0) {
        game->logFile = map["logFile"].toString();
    }
    if (map.constFind("showBgImages") != map.cend()) {
        game->showBgImages = (bool)map["showBgImages"].toInt();
    }
    game->textFont.fromString(map["textFont"].toString());
    QVariantMap controls = map["controls"].toJsonObject().toVariantMap();
    game->controlsMenu.set(Controls::HIDE_UI_ELEMENTS, controls["hideUIElements"].toInt());
    game->controlsMenu.set(Controls::TOGGLE_FULLSCREEN_MODE, controls["toggleFullscreenMode"].toInt());
    game->controlsMenu.set(Controls::GO_TO_PREVIOUS_MENU, controls["goToPreviousMenu"].toInt());
    isReady = true;
}

QJsonObject Config::serialize() const {
    QJsonObject jsonObj;
    jsonObj["fishingtime_object"] = "config";
    jsonObj["language"] = (int)game->activeLanguage;
    jsonObj["autoSavePeriod"] = game->autoSavePeriod;
    jsonObj["inventoryType"] = (int)game->inventoryType;
    jsonObj["colorTheme"] = (int)game->colorTheme;
    jsonObj["loggerLevel"] = (int)game->loggerLevel;
    jsonObj["logFile"] = game->logFile;
    jsonObj["showBgImages"] = (int)game->showBgImages;
    jsonObj["textFont"] = game->font().toString();
    QVariantMap controls;
    controls["hideUIElements"] = game->controlsMenu.get(Controls::HIDE_UI_ELEMENTS)[0];
    controls["toggleFullscreenMode"] = game->controlsMenu.get(Controls::TOGGLE_FULLSCREEN_MODE)[0];
    controls["goToPreviousMenu"] = game->controlsMenu.get(Controls::GO_TO_PREVIOUS_MENU)[0];
    jsonObj["controls"] = QJsonObject::fromVariantMap(controls);
    return jsonObj;
}

void Config::applyColorTheme(ColorTheme theme) {
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QPalette p(game->palette());
    switch (theme) {
    case ColorTheme::LIGHT:
        p.setColor(QPalette::Window, LIGHT_THEME_WINDOW_COLOR);
        p.setColor(QPalette::Button, LIGHT_THEME_WINDOW_COLOR);
        p.setColor(QPalette::Base, LIGHT_THEME_WINDOW_COLOR);
        p.setColor(QPalette::ButtonText, LIGHT_THEME_TEXT_COLOR);
        p.setColor(QPalette::WindowText, LIGHT_THEME_TEXT_COLOR);
        p.setColor(QPalette::Text, LIGHT_THEME_TEXT_COLOR);
        break;
    case ColorTheme::DARK:
        p.setColor(QPalette::Window, DARK_THEME_WINDOW_COLOR);
        p.setColor(QPalette::Button, DARK_THEME_WINDOW_COLOR);
        p.setColor(QPalette::Base, DARK_THEME_WINDOW_COLOR);
        p.setColor(QPalette::ButtonText, DARK_THEME_TEXT_COLOR);
        p.setColor(QPalette::WindowText, DARK_THEME_TEXT_COLOR);
        p.setColor(QPalette::Text, DARK_THEME_TEXT_COLOR);
        break;
    }
    game->setAutoFillBackground(true);
    game->setPalette(p);
    game->aboutMenu.setPalette(p);
    game->logger.setPalette(p);
    game->console.setPalette(p);
    game->gameMenu.getPopUpInventoryTable().setPalette(p);
    game->setFont(game->textFont);
    game->logger.setFont(game->textFont);
    game->console.setFont(game->textFont);
    game->aboutMenu.setFont(game->textFont);
    game->gameMenu.getPopUpInventoryTable().setFont(game->textFont);
    game->logger.info("Applied theme: " + QString::number((int)theme));
}
