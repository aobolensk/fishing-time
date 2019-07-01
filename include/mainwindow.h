#ifndef INCLUDE_MAINWINDOW_H_
#define INCLUDE_MAINWINDOW_H_
#include <QPushButton>
#include <QGridLayout>
#include <QString>
#include "mainmenu.h"
#include "loginmenu.h"
#include "gamemenu.h"
#include "user.h"

class MainWindow : public QWidget {
private:
    Q_OBJECT
private:
    QGridLayout grid;
    QString config_file;
public:
    MainMenu mainMenu;
    LoginMenu loginMenu;
    GameMenu gameMenu;
    QVector <User> users;
    int activeUser = -1;
    MainWindow(QWidget *parent, const QString &config_file);
    ~MainWindow();
};

#endif  // INCLUDE_MAINWINDOW_H_
