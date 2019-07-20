#include "mainmenu.h"
#include "game.h"

MainMenu::MainMenu(Game *game, QGridLayout *grid) :
        game(game),
        grid(grid) {
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
    startButton.setText(game->str.start);
    startButton.setVisible(true);
    startButton.setEnabled(true);

    settingsButton.setText(game->str.settings);
    settingsButton.setVisible(true);
    settingsButton.setEnabled(true);

    exitButton.setText(game->str.exit);
    exitButton.setVisible(true);
    exitButton.setEnabled(true);
}

void MainMenu::startFunction() {
    this->hide();
    game->loginMenu.display();
}

void MainMenu::settingsFunction() {
    this->hide();
    game->settingsMenu.display();
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
