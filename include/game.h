#ifndef INCLUDE_GAME_H_
#define INCLUDE_GAME_H_
#include <QCloseEvent>
#include <QDebug>
#include <QGridLayout>
#include <QPushButton>
#include <QString>
#include <QTimer>
#include <random>
#include "core.h"
#include "mainmenu.h"
#include "loginmenu.h"
#include "gamemenu.h"
#include "marketmenu.h"
#include "lotterymenu.h"
#include "storemenu.h"
#include "settingsmenu.h"
#include "appearancesettingsmenu.h"
#include "controlsmenu.h"
#include "netsmenu.h"
#include "statisticsmenu.h"
#include "itemstatisticsmenu.h"
#include "coinstatisticsmenu.h"
#include "usersettingsmenu.h"
#include "signupmenu.h"
#include "ratingmenu.h"
#include "creditsmenu.h"
#include "inventorymenu.h"
#include "userprofilemenu.h"
#include "locationmenu.h"
#include "aboutmenu.h"
#include "overlaywidget.h"
#include "logger.h"
#include "console.h"

class Game : public QWidget {
private:
    Q_OBJECT
private:
    QGridLayout grid;
    QString configFile;
private:
    void deserialize();
    void serialize();
private:
    void closeEvent(QCloseEvent *event);
    void resizeEvent(QResizeEvent *event);
private slots:
    void autoSaveFunction();
private:
    Menu *currentMenu = nullptr;
public:
    Core core;
    std::mt19937 &randomGenerator;
    Config &cfg;
    Dictionary &str;
    QVector <User> &users;
    QVector <Location> &locations;
    int &activeUser;
    int &activeLocation;
    Language &activeLanguage;
    QString &bgImagePath;
    bool &showBgImages;
    QDateTime &userTimestamp;
    InventoryType &inventoryType;
    ColorTheme &colorTheme;
    LoggerLevel &loggerLevel;
    QFont &textFont;
    QString &logFile;
    int &autoSavePeriod;
    Logger logger;
    Console console;
    MainMenu mainMenu;
    LoginMenu loginMenu;
    InventoryMenu popUpInventoryMenu;
    GameMenu gameMenu;
    MarketMenu marketMenu;
    LotteryMenu lotteryMenu;
    StoreMenu storeMenu;
    SettingsMenu settingsMenu;
    AppearanceSettingsMenu appearanceSettingsMenu;
    ControlsMenu controlsMenu;
    NetsMenu netsMenu;
    StatisticsMenu statisticsMenu;
    ItemStatisticsMenu itemStatisticsMenu;
    CoinStatisticsMenu coinStatisticsMenu;
    SignupMenu signupMenu;
    UsersettingsMenu usersettingsMenu;
    RatingMenu ratingMenu;
    CreditsMenu creditsMenu;
    InventoryMenu inventoryMenu;
    LocationMenu locationMenu;
    UserProfileMenu userProfileMenu;
    AboutMenu aboutMenu;
    OverlayWidget overlay;
    void setAutoSavePeriod(int periodInMinutes);
    void setConfigFile(const QString &newConfigFile);
    void setBackgroundImage(const QString &backgroundImagePath);
    int getAutoSavePeriod();
    QString getConfigFileName();
    void setCurrentMenu(Menu *menu);
    Menu *getCurrentMenu() const;
    void hideAll();
    QTimer autoSaveTimer;
public:
    Game(QWidget *parent, const QString &configFile);
    ~Game();
    friend QJsonObject Config::serialize(Game *game) const;
    friend void Config::deserialize(Game *game, const QVariantMap &map);
    void manualSave();
    void updateTimePlayed();
};

#endif  // INCLUDE_GAME_H_
