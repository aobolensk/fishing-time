#include <QMessageBox>
#include "usersettingsmenu.h"
#include "game.h"

UsersettingsMenu::UsersettingsMenu(Game *game, QGridLayout *grid) :
        game(game),
        grid(grid) {
    grid->addWidget(&usersettingsLabel, 0, 0, 1, 2);
    usersettingsLabel.setVisible(false);

    grid->addWidget(&changePasswordLabel, 1, 0);
    changePasswordLabel.setVisible(false);

    grid->addWidget(&oldPasswordLabel, 2, 0);
    oldPasswordLabel.setVisible(false);

    grid->addWidget(&newPasswordLabel, 2, 1);
    newPasswordLabel.setVisible(false);

    grid->addWidget(&newPasswordConfirmationLabel, 2, 2);
    newPasswordConfirmationLabel.setVisible(false);

    grid->addWidget(&oldPasswordText, 3, 0);
    oldPasswordText.setEchoMode(QLineEdit::Password);
    oldPasswordText.setVisible(false);
    oldPasswordText.setEnabled(false);

    grid->addWidget(&newPasswordText, 3, 1);
    newPasswordText.setEchoMode(QLineEdit::Password);
    newPasswordText.setVisible(false);
    newPasswordText.setEnabled(false);

    grid->addWidget(&newPasswordConfirmationText, 3, 2);
    newPasswordConfirmationText.setEchoMode(QLineEdit::Password);
    newPasswordConfirmationText.setVisible(false);
    newPasswordConfirmationText.setEnabled(false);

    grid->addWidget(&changePasswordButton, 4, 2);
    changePasswordButton.setEnabled(false);
    changePasswordButton.setVisible(false);
    connect(&changePasswordButton, SIGNAL(released()), this, SLOT(changePasswordFunction()));

    grid->addWidget(&deleteAccountButton, 5, 1);
    deleteAccountButton.setVisible(false);
    deleteAccountButton.setEnabled(false);
    connect(&deleteAccountButton, SIGNAL(released()), this, SLOT(deleteAccountFunction()));

    grid->addWidget(&backButton, 6, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void UsersettingsMenu::display() {
    game->installEventFilter(this);

    usersettingsLabel.setText(game->str.userSettingsText.arg(
        game->users[game->activeUser].getUsername()
    ));
    usersettingsLabel.setVisible(true);

    changePasswordLabel.setText(game->str.changePassword);
    changePasswordLabel.setVisible(true);

    oldPasswordLabel.setText(game->str.oldPassword);
    oldPasswordLabel.setVisible(true);

    newPasswordLabel.setText(game->str.newPassword);
    newPasswordLabel.setVisible(true);

    newPasswordConfirmationLabel.setText(game->str.newPasswordConfirmation);
    newPasswordConfirmationLabel.setVisible(true);

    oldPasswordText.setVisible(true);
    oldPasswordText.setEnabled(true);

    newPasswordText.setVisible(true);
    newPasswordText.setEnabled(true);

    newPasswordConfirmationText.setVisible(true);
    newPasswordConfirmationText.setEnabled(true);

    changePasswordButton.setText(game->str.changePassword);
    changePasswordButton.setEnabled(true);
    changePasswordButton.setVisible(true);

    deleteAccountButton.setText(game->str.deleteAccount);
    deleteAccountButton.setVisible(true);
    deleteAccountButton.setEnabled(true);

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);

    displayed = true;
}

void UsersettingsMenu::changePasswordFunction() {
    if (QCryptographicHash::hash(oldPasswordText.text().toLatin1(), QCryptographicHash::Md5) !=
            game->users[game->activeUser].getPasswordHash()) {
        QMessageBox::warning(game, game->str.fishingTime + ": " + game->str.warning, game->str.invalidOldPasswordWarning);
        return;
    }
    if (newPasswordText.text().toLatin1() != newPasswordConfirmationText.text().toLatin1()) {
        QMessageBox::warning(game, game->str.fishingTime + ": " + game->str.warning, game->str.confirmPasswordWarning);
        return;
    }
    game->users[game->activeUser].setPasswordHash(QCryptographicHash::hash(newPasswordText.text().toLatin1(), QCryptographicHash::Md5));
    QMessageBox::information(game, game->str.fishingTime + ": " + game->str.information, game->str.passwordIsChanged);
    oldPasswordText.setText("");
    newPasswordText.setText("");
    newPasswordConfirmationText.setText("");
}

void UsersettingsMenu::deleteAccountFunction() {
    QMessageBox::StandardButton deleteConfiramtionResult =
        QMessageBox::question(game, game->str.fishingTime, game->str.deleteAccountConfirmation,
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
    game->removeEventFilter(this);

    usersettingsLabel.setVisible(false);

    changePasswordLabel.setVisible(false);

    oldPasswordLabel.setVisible(false);

    newPasswordLabel.setVisible(false);

    newPasswordConfirmationLabel.setVisible(false);

    oldPasswordText.setVisible(false);
    oldPasswordText.setEnabled(false);

    newPasswordText.setVisible(false);
    newPasswordText.setEnabled(false);

    newPasswordConfirmationText.setVisible(false);
    newPasswordConfirmationText.setEnabled(false);

    changePasswordButton.setEnabled(false);
    changePasswordButton.setVisible(false);

    deleteAccountButton.setVisible(false);
    deleteAccountButton.setEnabled(false);

    backButton.setVisible(false);
    backButton.setEnabled(false);

    displayed = false;
}

UsersettingsMenu::~UsersettingsMenu() {

}
