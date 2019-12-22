#ifndef INCLUDE_GAME_H_
#define INCLUDE_GAME_H_
#include <QCloseEvent>
#include <QDateTime>
#include <QDebug>
#include <QGridLayout>
#include <QPushButton>
#include <QString>
#include <QTimer>
#include <random>
#include "mainmenu.h"
#include "loginmenu.h"
#include "popupinventorymenu.h"
#include "gamemenu.h"
#include "marketmenu.h"
#include "storemenu.h"
#include "settingsmenu.h"
#include "appearancesettingsmenu.h"
#include "controlsmenu.h"
#include "netsmenu.h"
#include "statisticsmenu.h"
#include "itemstatisticsmenu.h"
#include "usersettingsmenu.h"
#include "signupmenu.h"
#include "ratingmenu.h"
#include "creditsmenu.h"
#include "inventorymenu.h"
#include "userprofilemenu.h"
#include "locationmenu.h"
#include "aboutmenu.h"
#include "overlaywidget.h"
#include "user.h"
#include "location.h"
#include "dictionary.h"
#include "config.h"
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
    std::random_device rd;
    int autoSavePeriod = 3;
    Menu *currentMenu = nullptr;
public:
    QString logFile = "log.txt";
    std::mt19937 randomGenerator;
    Config cfg;
    Logger logger;
    Console console;
    Dictionary str;
    QVector <User> users;
    QVector <Location> locations;
    MainMenu mainMenu;
    LoginMenu loginMenu;
    PopUpInventoryMenu popUpInventoryMenu;
    GameMenu gameMenu;
    MarketMenu marketMenu;
    StoreMenu storeMenu;
    SettingsMenu settingsMenu;
    AppearanceSettingsMenu appearanceSettingsMenu;
    ControlsMenu controlsMenu;
    NetsMenu netsMenu;
    StatisticsMenu statisticsMenu;
    ItemStatisticsMenu itemStatisticsMenu;
    SignupMenu signupMenu;
    UsersettingsMenu usersettingsMenu;
    RatingMenu ratingMenu;
    CreditsMenu creditsMenu;
    InventoryMenu inventoryMenu;
    LocationMenu locationMenu;
    UserProfileMenu userProfileMenu;
    AboutMenu aboutMenu;
    OverlayWidget overlay;
    int activeUser = -1;
    int activeLocation = -1;
    QString bgImagePath;
    bool showBgImages = true;
    QDateTime userTimestamp;
    InventoryType inventoryType = InventoryType::POPUP;
    ColorTheme colorTheme = ColorTheme::LIGHT;
    LoggerLevel loggerLevel = LoggerLevel::RELEASE;
    QFont textFont = QFont("Noto Sans", 11, QFont::Normal, false);
    void setAutoSavePeriod(int periodInMinutes);
    void setConfigFile(const QString &newConfigFile);
    void setBackgroundImage(const QString &backgroundImagePath);
    int getAutoSavePeriod();
    QString getConfigFileName();
    void setCurrentMenu(Menu *menu);
    Menu *getCurrentMenu() const;
    Language activeLanguage = Language::English;
    QTimer autoSaveTimer;
public:
    Game(QWidget *parent, const QString &configFile);
    ~Game();
    friend QJsonObject Config::serialize() const;
    friend void Config::deserialize(const QVariantMap &map);
    void manualSave();
    void updateTimePlayed();
};

#endif  // INCLUDE_GAME_H_
