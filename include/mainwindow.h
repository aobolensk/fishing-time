#ifndef INCLUDE_MAINWINDOW_H_
#define INCLUDE_MAINWINDOW_H_
#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QDebug>
#include "mainmenu.h"

class MainWindow : public QWidget {
private:
    Q_OBJECT
private:
    QGridLayout *grid;
    MainMenu mainMenu;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};

#endif  // INCLUDE_MAINWINDOW_H_
