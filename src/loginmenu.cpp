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
    connect(&loginButton, SIGNAL(released()), this, SLOT(backFunction()));
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

void LoginMenu::hide() {
    loginText.setVisible(false);
    loginButton.setVisible(false);
    disconnect(&loginButton, SIGNAL(released()), this, SLOT(backFunction()));
    signUpButton.setVisible(false);
    disconnect(&signUpButton, SIGNAL(released()), this, SLOT(backFunction()));
    backButton.setVisible(false);
    disconnect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

LoginMenu::~LoginMenu() {
    
}
