#include <QMessageBox>
#include "loginmenu.h"
#include "mainwindow.h"

LoginMenu::LoginMenu(MainWindow *w, QGridLayout *g) :
        window(w),
        grid(g) {
    grid->addWidget(&loginText, 0, 0);
    loginText.setVisible(false);

    grid->addWidget(&loginButton, 0, 1);
    loginButton.setVisible(false);
    connect(&loginButton, SIGNAL(released()), this, SLOT(loginFunction()));

    connect(&signUpButton, SIGNAL(released()), this, SLOT(signUpFunction()));
    grid->addWidget(&signUpButton, 0, 2);
    signUpButton.setVisible(false);

    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
    grid->addWidget(&backButton, 1, 1);
    backButton.setVisible(false);
}

void LoginMenu::display() {
    loginText.setText(window->str.enterYourLoginHereText);
    loginText.setVisible(true);

    loginButton.setText(window->str.logIn);
    loginButton.setVisible(true);

    signUpButton.setText(window->str.signUp);
    signUpButton.setVisible(true);

    backButton.setText(window->str.back);
    backButton.setVisible(true);
}

void LoginMenu::backFunction() {
    this->hide();
    window->mainMenu.display();
}

void LoginMenu::loginFunction() {
    for (int i = 0; i < window->users.size(); ++i) {
        if (window->users[i].getUsername() == loginText.text()) {
            qDebug() << "Logged in as " << loginText.text();
            window->activeUser = i;
            window->activeLocation = 0;
            this->hide();
            window->gameMenu.display();
            return;
        }
    }
    QMessageBox::warning(window, window->str.warning, window->str.invalidLoginText);
}

void LoginMenu::signUpFunction() {
    for (int i = 0; i < window->users.size(); ++i) {
        if (window->users[i].getUsername() == loginText.text()) {
            QMessageBox::warning(window, window->str.warning, window->str.thisUserAlreadyExistsText);
            return;
        }
    }
    window->users.push_back(User(loginText.text()));
    QMessageBox::information(window, window->str.information,
                             window->str.newUserCreatedText.arg(loginText.text()));
}

void LoginMenu::hide() {
    loginText.setVisible(false);
    loginButton.setVisible(false);
    signUpButton.setVisible(false);
    backButton.setVisible(false);
}

LoginMenu::~LoginMenu() {
    
}
