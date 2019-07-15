#ifndef INCLUDE_MAINWINDOW_H_
#define INCLUDE_MAINWINDOW_H_
#include <QPushButton>
#include <QGridLayout>
#include <QString>
#include <QTimer>
#include "mainmenu.h"
#include "loginmenu.h"
#include "gamemenu.h"
#include "marketmenu.h"
#include "storemenu.h"
#include "settingsmenu.h"
#include "user.h"
#include "location.h"
#include "dictionary.h"
#include "config.h"

class MainWindow : public QWidget {
private:
    Q_OBJECT
private:
    QGridLayout grid;
    QString config_file;
private:
    void deserialize();
    void serialize();
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
    int activeUser = -1;
    int activeLocation = -1;
    void setAutoSavePeriod(int period);
    Language activeLanguage = Language::English;
    QTimer autoSaveTimer;
    MainWindow(QWidget *parent, const QString &config_file);
    ~MainWindow();
};

#endif  // INCLUDE_MAINWINDOW_H_
