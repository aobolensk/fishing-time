#include <QHeaderView>
#include <QSettings>
#include <QStringList>
#include "userprofilemenu.h"
#include "game.h"

UserProfileMenu::UserProfileMenu(Game *game, QGridLayout *grid) :
        Menu(game, grid) {

    grid->addWidget(&userProfileLabel, 1, 0, 1, 3);
    userProfileLabel.setWordWrap(true);
    userProfileLabel.setVisible(false);

    grid->addWidget(&backButton, 4, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void UserProfileMenu::display() {
    this->pre_display();

    userProfileLabel.setText(game->str.userProfileText.arg(
        game->users[game->activeUser].getUsername(),
        QString::number(game->users[game->activeUser].getLevel()),
        QString::number(game->users[game->activeUser].getRemainingForNextLevel()),
        QString::number(game->users[game->activeUser].getNeededForNextLevel()),
        QString::number(game->users[game->activeUser].getCoins())
    ));
    userProfileLabel.setVisible(true);

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);

    displayed = true;
}

void UserProfileMenu::backFunction() {
    this->hide();
    game->gameMenu.display();
}

void UserProfileMenu::hide() {
    this->pre_hide();

    userProfileLabel.setVisible(false);

    backButton.setVisible(false);
    backButton.setEnabled(false);

    displayed = false;
}

UserProfileMenu::~UserProfileMenu() {

}
