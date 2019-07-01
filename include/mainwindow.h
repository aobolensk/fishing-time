#ifndef INCLUDE_MAINWINDOW_H_
#define INCLUDE_MAINWINDOW_H_
#include <QPushButton>
#include <QGridLayout>
#include <QString>
#include "mainmenu.h"
#include "loginmenu.h"
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
    QVector <User> users;
    MainWindow(QWidget *parent, const QString &config_file);
    ~MainWindow();
};

#endif  // INCLUDE_MAINWINDOW_H_
