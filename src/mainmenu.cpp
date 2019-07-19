#include "mainmenu.h"
#include "mainwindow.h"

MainMenu::MainMenu(MainWindow *w, QGridLayout *g) :
        window(w),
        grid(g) {
    grid->addWidget(&startButton, 0, 1);
    startButton.setVisible(false);
    startButton.setEnabled(false);
    connect(&startButton, SIGNAL(released()), this, SLOT(startFunction()));

    grid->addWidget(&settingsButton, 1, 1);
    settingsButton.setVisible(false);
    settingsButton.setEnabled(false);
    connect(&settingsButton, SIGNAL(released()), this, SLOT(settingsFunction()));

    grid->addWidget(&exitButton, 2, 1);
    exitButton.setVisible(false);
    exitButton.setEnabled(false);
    connect(&exitButton, SIGNAL(released()), this, SLOT(exitFunction()));

}

void MainMenu::display() {
    startButton.setText(window->str.start);
    startButton.setVisible(true);
    startButton.setEnabled(true);

    settingsButton.setText(window->str.settings);
    settingsButton.setVisible(true);
    settingsButton.setEnabled(true);

    exitButton.setText(window->str.exit);
    exitButton.setVisible(true);
    exitButton.setEnabled(true);
}

void MainMenu::startFunction() {
    this->hide();
    window->loginMenu.display();
}

void MainMenu::settingsFunction() {
    this->hide();
    window->settingsMenu.display();
}

void MainMenu::exitFunction() {
    this->hide();
    QApplication::quit();
}

void MainMenu::hide() {
    startButton.setVisible(false);
    startButton.setEnabled(false);

    settingsButton.setVisible(false);
    settingsButton.setEnabled(false);

    exitButton.setVisible(false);
    exitButton.setEnabled(false);
}

MainMenu::~MainMenu() {
    
}
