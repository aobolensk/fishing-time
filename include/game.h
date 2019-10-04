#ifndef INCLUDE_GAME_H_
#define INCLUDE_GAME_H_
#include <random>
#include <QPushButton>
#include <QGridLayout>
#include <QString>
#include <QTimer>
#include <QCloseEvent>
#include <QDateTime>
#include "mainmenu.h"
#include "loginmenu.h"
#include "gamemenu.h"
#include "marketmenu.h"
#include "storemenu.h"
#include "settingsmenu.h"
#include "netsmenu.h"
#include "statisticsmenu.h"
#include "usersettingsmenu.h"
#include "signupmenu.h"
#include "ratingmenu.h"
#include "inventorymenu.h"
#include "locationmenu.h"
#include "aboutmenu.h"
#include "user.h"
#include "location.h"
#include "dictionary.h"
#include "config.h"
#include "console.h"

class Game : public QWidget {
private:
    Q_OBJECT
private:
    QGridLayout grid;
    QString config_file;
private:
    void deserialize();
    void serialize();
private:
    void closeEvent(QCloseEvent *event);
private slots:
    void autoSaveFunction();
private:
    std::random_device rd;
    int autoSavePeriod = 3;
public:
    std::mt19937 randomGenerator;
    Config cfg;
    Console console;
    Dictionary str;
    QVector <User> users;
    QVector <Location> locations;
    MainMenu mainMenu;
    LoginMenu loginMenu;
    GameMenu gameMenu;
    MarketMenu marketMenu;
    StoreMenu storeMenu;
    SettingsMenu settingsMenu;
    NetsMenu netsMenu;
    StatisticsMenu statisticsMenu;
    SignupMenu signupMenu;
    UsersettingsMenu usersettingsMenu;
    RatingMenu ratingMenu;
    InventoryMenu inventoryMenu;
    LocationMenu locationMenu;
    AboutMenu aboutMenu;
    int activeUser = -1;
    int activeLocation = -1;
    QDateTime userTimestamp;
    InventoryType inventoryType = InventoryType::POPUP;
    ColorTheme colorTheme = ColorTheme::LIGHT;
    QFont textFont = QFont("Noto Sans", 11, QFont::Normal, false);
    void setAutoSavePeriod(int periodInMinutes);
    int getAutoSavePeriod();
    QString getConfigFileName();
    Language activeLanguage = Language::English;
    QTimer autoSaveTimer;
public:
    Game(QWidget *parent, const QString &config_file);
    ~Game();
    friend QJsonObject Config::serialize() const;
    friend void Config::deserialize(const QVariantMap &map);
    void hideCurrentMenu();
    void manualSave();
    void updateTimePlayed();
};

#endif  // INCLUDE_GAME_H_
