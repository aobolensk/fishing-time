#include <QHeaderView>
#include <QSettings>
#include <QStringList>
#include "userprofilemenu.h"
#include "game.h"

UserProfileMenu::UserProfileMenu(Game *game, QGridLayout *grid) :
        Menu(game, grid) {

    grid->addWidget(&backButton, 4, 2);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void UserProfileMenu::display() {
    this->pre_display();

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

    backButton.setVisible(false);
    backButton.setEnabled(false);

    displayed = false;
}

UserProfileMenu::~UserProfileMenu() {

}
