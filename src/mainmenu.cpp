#include <QDesktopServices>
#include "mainmenu.h"
#include "game.h"

MainMenu::MainMenu(Game *game, QGridLayout *grid) :
        game(game),
        grid(grid) {
    grid->addWidget(&infoLabel, 0, 2);
    infoLabel.setVisible(false);
    infoLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    grid->addWidget(&consoleButton, 1, 2);
    consoleButton.setVisible(false);
    consoleButton.setEnabled(false);
    connect(&consoleButton, SIGNAL(released()), this, SLOT(consoleFunction()));

    grid->addWidget(&startButton, 0, 1);
    startButton.setVisible(false);
    startButton.setEnabled(false);
    connect(&startButton, SIGNAL(released()), this, SLOT(startFunction()));

    grid->addWidget(&settingsButton, 1, 1);
    settingsButton.setVisible(false);
    settingsButton.setEnabled(false);
    connect(&settingsButton, SIGNAL(released()), this, SLOT(settingsFunction()));

    grid->addWidget(&ratingButton, 2, 1);
    ratingButton.setVisible(false);
    ratingButton.setEnabled(false);
    connect(&ratingButton, SIGNAL(released()), this, SLOT(ratingFunction()));

    grid->addWidget(&aboutButton, 3, 1);
    aboutButton.setVisible(false);
    aboutButton.setEnabled(false);
    connect(&aboutButton, SIGNAL(released()), this, SLOT(aboutFunction()));

    grid->addWidget(&reportButton, 3, 2);
    reportButton.setVisible(false);
    reportButton.setEnabled(false);
    connect(&reportButton, SIGNAL(released()), this, SLOT(reportFunction()));

    grid->addWidget(&exitButton, 4, 1);
    exitButton.setVisible(false);
    exitButton.setEnabled(false);
    connect(&exitButton, SIGNAL(released()), this, SLOT(exitFunction()));
}

void MainMenu::display() {
    game->installEventFilter(this);

    infoLabel.setText(game->str.mainMenuText.arg(
        game->activeUser == -1 ? "" : game->users[game->activeUser].getUsername()
    ));
    infoLabel.setVisible(true);

    consoleButton.setText(game->str.console);
    consoleButton.setVisible(true);
    consoleButton.setEnabled(true);

    startButton.setText(game->str.start);
    startButton.setVisible(true);
    startButton.setEnabled(true);

    settingsButton.setText(game->str.settings);
    settingsButton.setVisible(true);
    settingsButton.setEnabled(true);

    ratingButton.setText(game->str.rating);
    ratingButton.setVisible(true);
    ratingButton.setEnabled(true);

    aboutButton.setText(game->str.about);
    aboutButton.setVisible(true);
    aboutButton.setEnabled(true);

    reportButton.setText(game->str.reportAnError);
    reportButton.setVisible(true);
    reportButton.setEnabled(true);

    exitButton.setText(game->str.exit);
    exitButton.setVisible(true);
    exitButton.setEnabled(true);

    displayed = true;
}

void MainMenu::consoleFunction() {
    game->console.display();
}

void MainMenu::startFunction() {
    if (game->activeUser == -1) {
        this->hide();
        game->loginMenu.display();
    } else {
        this->hide();
        game->gameMenu.display();
    }
}

void MainMenu::settingsFunction() {
    this->hide();
    game->settingsMenu.display();
}

void MainMenu::ratingFunction() {
    this->hide();
    game->ratingMenu.display();
}

void MainMenu::aboutFunction() {
    game->aboutMenu.display();
}

void MainMenu::reportFunction() {
    QDesktopServices::openUrl(QUrl("https://github.com/gooddoog/fishing-time/issues"));
}

void MainMenu::exitFunction() {
    this->hide();
    QApplication::quit();
}

void MainMenu::hide() {
    game->removeEventFilter(this);

    infoLabel.setVisible(false);

    consoleButton.setVisible(false);
    consoleButton.setEnabled(false);

    startButton.setVisible(false);
    startButton.setEnabled(false);

    settingsButton.setVisible(false);
    settingsButton.setEnabled(false);

    ratingButton.setVisible(false);
    ratingButton.setEnabled(false);

    aboutButton.setVisible(false);
    aboutButton.setEnabled(false);

    reportButton.setVisible(false);
    reportButton.setEnabled(false);

    exitButton.setVisible(false);
    exitButton.setEnabled(false);

    displayed = false;
}

MainMenu::~MainMenu() {

}
