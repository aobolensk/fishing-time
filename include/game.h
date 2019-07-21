#ifndef INCLUDE_GAME_H_
#define INCLUDE_GAME_H_
#include <QPushButton>
#include <QGridLayout>
#include <QString>
#include <QTimer>
#include <QCloseEvent>
#include "mainmenu.h"
#include "loginmenu.h"
#include "gamemenu.h"
#include "marketmenu.h"
#include "storemenu.h"
#include "settingsmenu.h"
#include "netsmenu.h"
#include "user.h"
#include "location.h"
#include "dictionary.h"
#include "config.h"

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
    int autoSavePeriod = 3;
public:
    Config cfg;
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
    int activeUser = -1;
    int activeLocation = -1;
    void setAutoSavePeriod(int periodInMinutes);
    Language activeLanguage = Language::English;
    QTimer autoSaveTimer;
    Game(QWidget *parent, const QString &config_file);
    ~Game();
    friend QByteArray Config::serialize() const;
    friend void Config::deserialize(const QVariantMap &map);
};

#endif  // INCLUDE_GAME_H_
