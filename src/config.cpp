#include <QStyleFactory>
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
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QPalette p(game->palette());
    switch (theme) {
    case ColorTheme::LIGHT:
        p.setColor(QPalette::Window, QColor(250, 250, 250));
        p.setColor(QPalette::Button, QColor(250, 250, 250));
        p.setColor(QPalette::Base, QColor(250, 250, 250));
        p.setColor(QPalette::ButtonText, QColor(20, 20, 20));
        p.setColor(QPalette::WindowText, QColor(20, 20, 20));
        p.setColor(QPalette::Text, QColor(20, 20, 20));
        break;
    case ColorTheme::DARK:
        p.setColor(QPalette::Window, QColor(64, 64, 64));
        p.setColor(QPalette::Button, QColor(64, 64, 64));
        p.setColor(QPalette::Base, QColor(64, 64, 64));
        p.setColor(QPalette::ButtonText, QColor(240, 240, 240));
        p.setColor(QPalette::WindowText, QColor(240, 240, 240));
        p.setColor(QPalette::Text, QColor(240, 240, 240));
        break;
    }
    game->setAutoFillBackground(true);
    game->setPalette(p);
    game->aboutMenu.setPalette(p);
    game->console.setPalette(p);
    game->gameMenu.getPopUpInventoryTable().setPalette(p);
    game->setFont(game->textFont);
    game->console.setFont(game->textFont);
    game->aboutMenu.setFont(game->textFont);
    game->gameMenu.getPopUpInventoryTable().setFont(game->textFont);
    qDebug() << "Applied theme:" << (int)theme;
}
