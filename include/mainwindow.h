#ifndef INCLUDE_MAINWINDOW_H_
#define INCLUDE_MAINWINDOW_H_
#include <QPushButton>
#include <QGridLayout>
#include "mainmenu.h"
#include "loginmenu.h"

class MainWindow : public QWidget {
private:
    Q_OBJECT
private:
    QGridLayout grid;
public:
    MainMenu mainMenu;
    LoginMenu loginMenu;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};

#endif  // INCLUDE_MAINWINDOW_H_
