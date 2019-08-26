#include <QMessageBox>
#include "signupmenu.h"
#include "game.h"

SignupMenu::SignupMenu(Game *game, QGridLayout *grid) :
        game(game),
        grid(grid) {
    grid->addWidget(&signupLabel, 0, 0, 1, 3);
    signupLabel.setWordWrap(true);
    signupLabel.setVisible(false);
    signupLabel.setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

    grid->addWidget(&loginLabel, 1, 0);
    loginLabel.setVisible(false);

    grid->addWidget(&passwordLabel, 2, 0);
    passwordLabel.setVisible(false);

    grid->addWidget(&passwordConfirmationLabel, 3, 0);
    passwordConfirmationLabel.setVisible(false);

    grid->addWidget(&loginText, 1, 1);
    loginText.setVisible(false);
    loginText.setEnabled(false);
    QObject::connect(&loginText, &QLineEdit::returnPressed, [this]() { signUpFunction(); });

    grid->addWidget(&passwordText, 2, 1);
    passwordText.setEchoMode(QLineEdit::Password);
    passwordText.setVisible(false);
    passwordText.setEnabled(false);
    QObject::connect(&passwordText, &QLineEdit::returnPressed, [this]() { signUpFunction(); });

    grid->addWidget(&passwordConfirmationText, 3, 1);
    passwordConfirmationText.setEchoMode(QLineEdit::Password);
    passwordConfirmationText.setVisible(false);
    passwordConfirmationText.setEnabled(false);
    QObject::connect(&passwordConfirmationText, &QLineEdit::returnPressed, [this]() { signUpFunction(); });

    connect(&signUpButton, SIGNAL(released()), this, SLOT(signUpFunction()));
    grid->addWidget(&signUpButton, 1, 2);
    signUpButton.setVisible(false);
    signUpButton.setEnabled(false);

    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
    grid->addWidget(&backButton, 4, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
}

void SignupMenu::display() {
    signupLabel.setText(game->str.signupMenuText);
    signupLabel.setVisible(true);

    loginLabel.setText(game->str.username);
    loginLabel.setVisible(true);

    passwordLabel.setText(game->str.password);
    passwordLabel.setVisible(true);

    passwordConfirmationLabel.setText(game->str.confirmPassword);
    passwordConfirmationLabel.setVisible(true);

    loginText.setText("");
    loginText.setVisible(true);
    loginText.setEnabled(true);

    passwordText.setText("");
    passwordText.setVisible(true);
    passwordText.setEnabled(true);

    passwordConfirmationText.setText("");
    passwordConfirmationText.setVisible(true);
    passwordConfirmationText.setEnabled(true);

    signUpButton.setText(game->str.signUp);
    signUpButton.setVisible(true);
    signUpButton.setEnabled(true);

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);
}

void SignupMenu::backFunction() {
    this->hide();
    game->loginMenu.display();
}

void SignupMenu::signUpFunction() {
    if (loginText.text() == "") {
        QMessageBox::warning(game, game->str.fishingTime + ": " + game->str.warning, game->str.emptyLoginWarning);
        return;
    }
    if (passwordText.text() == "") {
        QMessageBox::StandardButton emptyPasswordResult = 
            QMessageBox::question(game, game->str.fishingTime, game->str.emptyPasswordWarning,
            QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);
        if (emptyPasswordResult != QMessageBox::Yes) {
            return;
        }
    }
    if (passwordText.text() != passwordConfirmationText.text()) {
        QMessageBox::warning(game, game->str.fishingTime + ": " + game->str.warning, game->str.confirmPasswordWarning);
        return;
    }
    for (int i = 0; i < game->users.size(); ++i) {
        if (game->users[i].getUsername() == loginText.text()) {
            QMessageBox::warning(game, game->str.fishingTime + ": " + game->str.warning, game->str.thisUserAlreadyExistsText);
            return;
        }
    }
    game->users.push_back(User(loginText.text(), passwordText.text()));
    QMessageBox::information(game, game->str.fishingTime + ": " + game->str.information,
                             game->str.newUserCreatedText.arg(loginText.text()));
    backFunction();
}

void SignupMenu::hide() {
    signupLabel.setVisible(false);

    loginLabel.setVisible(false);

    passwordLabel.setVisible(false);

    passwordConfirmationLabel.setVisible(false);

    loginText.setVisible(false);
    loginText.setEnabled(false);

    passwordText.setVisible(false);
    passwordText.setEnabled(false);

    passwordConfirmationText.setVisible(false);
    passwordConfirmationText.setEnabled(false);

    signUpButton.setVisible(false);
    signUpButton.setEnabled(false);

    backButton.setVisible(false);
    backButton.setEnabled(false);
}

SignupMenu::~SignupMenu() {
    
}