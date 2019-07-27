#include "usersettingsmenu.h"
#include "game.h"

UsersettingsMenu::UsersettingsMenu(Game *game, QGridLayout *grid) :
        game(game),
        grid(grid) {
    grid->addWidget(&usersettingsText, 0, 0, 1, 2);
    usersettingsText.setVisible(false);

    grid->addWidget(&backButton, 1, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void UsersettingsMenu::display() {
    usersettingsText.setText(game->str.userSettingsText.arg(
        game->users[game->activeUser].getUsername()
    ));
    usersettingsText.setVisible(true);

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);
}

void UsersettingsMenu::backFunction() {
    this->hide();
    game->gameMenu.display();
}

void UsersettingsMenu::hide() {
    usersettingsText.setVisible(false);

    backButton.setVisible(false);
    backButton.setEnabled(false);
}

UsersettingsMenu::~UsersettingsMenu() {

}
