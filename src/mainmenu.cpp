#include "mainmenu.h"
#include "mainwindow.h"

MainMenu::MainMenu(MainWindow *w, QGridLayout *g) :
        window(w),
        startButton(QPushButton(window)),
        exitButton(QPushButton(window)),
        grid(g) {

    grid->addWidget(&startButton, 0, 1);
    startButton.setVisible(false);
    connect(&startButton, SIGNAL(released()), this, SLOT(startFunction()));

    grid->addWidget(&exitButton, 1, 1);
    exitButton.setVisible(false);
    connect(&exitButton, SIGNAL(released()), this, SLOT(exitFunction()));
}

void MainMenu::display() {
    startButton.setText(window->str.start);
    startButton.setVisible(true);

    exitButton.setText(window->str.exit);
    exitButton.setVisible(true);
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
    exitButton.setVisible(false);
}

MainMenu::~MainMenu() {
    
}
