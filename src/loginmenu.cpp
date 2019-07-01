#include <QMessageBox>
#include "loginmenu.h"
#include "mainwindow.h"

LoginMenu::LoginMenu(MainWindow *w, QGridLayout *g) :
        window(w),
        loginButton(QPushButton(window)),
        signUpButton(QPushButton(window)),
        backButton(QPushButton(window)),
        grid(g) {
    grid->addWidget(&loginText, 0, 0);
    loginText.setVisible(false);
    grid->addWidget(&loginButton, 0, 1);
    loginButton.setVisible(false);
    grid->addWidget(&signUpButton, 0, 2);
    signUpButton.setVisible(false);
    grid->addWidget(&backButton, 1, 1);
    backButton.setVisible(false);
}

void LoginMenu::display() {
    loginText.setText("Enter your login here");
    loginText.setVisible(true);
    loginButton.setText("Log in");
    loginButton.setVisible(true);
    connect(&loginButton, SIGNAL(released()), this, SLOT(loginFunction()));
    signUpButton.setText("Sign up");
    signUpButton.setVisible(true);
    connect(&signUpButton, SIGNAL(released()), this, SLOT(backFunction()));
    backButton.setText("Back");
    backButton.setVisible(true);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
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
            this->hide();
            window->gameMenu.display();
            return;
        }
    }
    QMessageBox::warning(window, "Warning", "Invalid login");
}

void LoginMenu::hide() {
    loginText.setVisible(false);
    loginButton.setVisible(false);
    disconnect(&loginButton, SIGNAL(released()), this, SLOT(loginFunction()));
    signUpButton.setVisible(false);
    disconnect(&signUpButton, SIGNAL(released()), this, SLOT(backFunction()));
    backButton.setVisible(false);
    disconnect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

LoginMenu::~LoginMenu() {
    
}
