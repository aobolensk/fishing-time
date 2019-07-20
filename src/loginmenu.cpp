#include <QMessageBox>
#include "loginmenu.h"
#include "game.h"

LoginMenu::LoginMenu(Game *game, QGridLayout *grid) :
        game(game),
        grid(grid) {
    grid->addWidget(&loginText, 0, 0);
    loginText.setVisible(false);
    loginText.setEnabled(false);

    grid->addWidget(&loginButton, 0, 1);
    loginButton.setVisible(false);
    loginButton.setEnabled(false);
    connect(&loginButton, SIGNAL(released()), this, SLOT(loginFunction()));

    connect(&signUpButton, SIGNAL(released()), this, SLOT(signUpFunction()));
    grid->addWidget(&signUpButton, 0, 2);
    signUpButton.setVisible(false);
    signUpButton.setEnabled(false);

    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
    grid->addWidget(&backButton, 1, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
}

void LoginMenu::display() {
    loginText.setText(game->str.enterYourLoginHereText);
    loginText.setVisible(true);
    loginText.setEnabled(true);

    loginButton.setText(game->str.logIn);
    loginButton.setVisible(true);
    loginButton.setEnabled(true);

    signUpButton.setText(game->str.signUp);
    signUpButton.setVisible(true);
    signUpButton.setEnabled(true);

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);
}

void LoginMenu::backFunction() {
    this->hide();
    game->mainMenu.display();
}

void LoginMenu::loginFunction() {
    for (int i = 0; i < game->users.size(); ++i) {
        if (game->users[i].getUsername() == loginText.text()) {
            qDebug() << "Logged in as " << loginText.text();
            game->activeUser = i;
            game->activeLocation = 0;
            this->hide();
            game->gameMenu.display();
            return;
        }
    }
    QMessageBox::warning(game, game->str.warning, game->str.invalidLoginText);
}

void LoginMenu::signUpFunction() {
    for (int i = 0; i < game->users.size(); ++i) {
        if (game->users[i].getUsername() == loginText.text()) {
            QMessageBox::warning(game, game->str.warning, game->str.thisUserAlreadyExistsText);
            return;
        }
    }
    game->users.push_back(User(loginText.text()));
    QMessageBox::information(game, game->str.information,
                             game->str.newUserCreatedText.arg(loginText.text()));
}

void LoginMenu::hide() {
    loginText.setVisible(false);
    loginText.setEnabled(false);

    loginButton.setVisible(false);
    loginButton.setEnabled(false);

    signUpButton.setVisible(false);
    signUpButton.setEnabled(false);

    backButton.setVisible(false);
    backButton.setEnabled(false);
}

LoginMenu::~LoginMenu() {
    
}
