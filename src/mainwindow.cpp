#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent),
        grid(QGridLayout(this)),
        mainMenu(MainMenu(this, &grid)),
        loginMenu(LoginMenu(this, &grid)) {
    this->setGeometry(QRect(QPoint(100, 100), QSize(640, 480)));
    mainMenu.display();
    setLayout(&grid);
    grid.setColumnStretch(0, 1);
    grid.setColumnStretch(1, 1);
    grid.setColumnStretch(2, 1);
}

MainWindow::~MainWindow() {
    
}
