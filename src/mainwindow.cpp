#include <QCoreApplication>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent),
        grid(new QGridLayout(this)),
        mainMenu(MainMenu(this, grid)) {
    this->setGeometry(QRect(QPoint(100, 100), QSize(640, 480)));
    mainMenu.display();
    setLayout(grid);
}

MainWindow::~MainWindow() {
    
}
