#ifndef INCLUDE_MAINWINDOW_H_
#define INCLUDE_MAINWINDOW_H_
#include <QPushButton>
#include <QGridLayout>
#include <QString>
#include "mainmenu.h"
#include "loginmenu.h"
#include "gamemenu.h"
#include "marketmenu.h"
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
public:
    Config cfg;
    Dictionary str;
    MainMenu mainMenu;
    LoginMenu loginMenu;
    GameMenu gameMenu;
    MarketMenu marketMenu;
    QVector <User> users;
    QVector <Location> locations;
    int activeUser = -1;
    int activeLocation = -1;
    MainWindow(QWidget *parent, const QString &config_file);
    ~MainWindow();
};

#endif  // INCLUDE_MAINWINDOW_H_
