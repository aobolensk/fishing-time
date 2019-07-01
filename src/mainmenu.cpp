#include "mainmenu.h"
#include "mainwindow.h"

MainMenu::MainMenu(MainWindow *w, QGridLayout *g) :
        window(w),
        startButton(QPushButton(window)),
        exitButton(QPushButton(window)),
        grid(g) {
    grid->addWidget(&startButton, 0, 1);
    grid->addWidget(&exitButton, 1, 1);
    startButton.setVisible(false);
    exitButton.setVisible(false);
}

void MainMenu::display() {
    startButton.setText("Start");
    startButton.setVisible(true);
    connect(&startButton, SIGNAL(released()), this, SLOT(startFunction()));
    exitButton.setText("Exit");
    exitButton.setVisible(true);
    connect(&exitButton, SIGNAL(released()), this, SLOT(exitFunction()));
}

void MainMenu::startFunction() {
    this->hide();
    window->loginMenu.display();
}

void MainMenu::exitFunction() {
    this->hide();
    QApplication::quit();
}

void MainMenu::hide() {
    startButton.setVisible(false);
    disconnect(&startButton, SIGNAL(released()), this, SLOT(startFunction()));
    exitButton.setVisible(false);
    disconnect(&exitButton, SIGNAL(released()), this, SLOT(exitFunction()));
}

MainMenu::~MainMenu() {
    
}
