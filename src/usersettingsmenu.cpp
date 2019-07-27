#include <QMessageBox>
#include "usersettingsmenu.h"
#include "game.h"

UsersettingsMenu::UsersettingsMenu(Game *game, QGridLayout *grid) :
        game(game),
        grid(grid) {
    grid->addWidget(&usersettingsText, 0, 0, 1, 2);
    usersettingsText.setVisible(false);

    grid->addWidget(&deleteAccountButton, 1, 1);
    deleteAccountButton.setVisible(false);
    deleteAccountButton.setEnabled(false);
    connect(&deleteAccountButton, SIGNAL(released()), this, SLOT(deleteAccountFunction()));

    grid->addWidget(&backButton, 2, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void UsersettingsMenu::display() {
    usersettingsText.setText(game->str.userSettingsText.arg(
        game->users[game->activeUser].getUsername()
    ));
    usersettingsText.setVisible(true);

    deleteAccountButton.setText(game->str.deleteAccount);
    deleteAccountButton.setVisible(true);
    deleteAccountButton.setEnabled(true);

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);
}

void UsersettingsMenu::deleteAccountFunction() {
    QMessageBox::StandardButton deleteConfiramtionResult =
        QMessageBox::question(game, "fishing-time", game->str.deleteAccountConfirmation,
        QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);
    if (deleteConfiramtionResult == QMessageBox::Yes) {
        game->netsMenu.foldNets();
        game->users.erase(game->users.begin() + game->activeUser);
        game->activeUser = -1;
        game->activeLocation = -1;
        this->hide();
        game->mainMenu.display();
    }
}

void UsersettingsMenu::backFunction() {
    this->hide();
    game->gameMenu.display();
}

void UsersettingsMenu::hide() {
    usersettingsText.setVisible(false);

    deleteAccountButton.setVisible(false);
    deleteAccountButton.setEnabled(false);

    backButton.setVisible(false);
    backButton.setEnabled(false);
}

UsersettingsMenu::~UsersettingsMenu() {

}
