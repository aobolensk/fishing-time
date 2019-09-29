#include <random>
#include <QMessageBox>
#include "loginmenu.h"
#include "game.h"

LoginMenu::LoginMenu(Game *game, QGridLayout *grid) :
        game(game),
        grid(grid) {
    grid->addWidget(&loginSelector, 0, 0);
    loginSelector.setVisible(false);
    loginSelector.setEnabled(false);

    grid->addWidget(&passwordText, 1, 0);
    passwordText.setEchoMode(QLineEdit::Password);
    passwordText.setVisible(false);
    passwordText.setEnabled(false);
    QObject::connect(&passwordText, &QLineEdit::returnPressed, [this]() { loginFunction(); });

    grid->addWidget(&loginButton, 0, 1);
    loginButton.setVisible(false);
    loginButton.setEnabled(false);
    connect(&loginButton, SIGNAL(released()), this, SLOT(loginFunction()));

    connect(&signUpButton, SIGNAL(released()), this, SLOT(signUpFunction()));
    grid->addWidget(&signUpButton, 0, 2);
    signUpButton.setVisible(false);
    signUpButton.setEnabled(false);

    connect(&demoButton, SIGNAL(released()), this, SLOT(demoFunction()));
    grid->addWidget(&demoButton, 1, 2);
    demoButton.setVisible(false);
    demoButton.setEnabled(false);

    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
    grid->addWidget(&backButton, 2, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
}

bool LoginMenu::isDisplayed() const {
    return displayed;
}

void LoginMenu::display() {
    for (int i = 0; i < game->users.count(); ++i) {
        loginSelector.addItem(game->users[i].getUsername());
    }
    loginSelector.setVisible(true);
    loginSelector.setEnabled(true);

    passwordText.setText("");
    passwordText.setVisible(true);
    passwordText.setEnabled(true);

    loginButton.setText(game->str.logIn);
    loginButton.setVisible(true);
    loginButton.setEnabled(true);

    signUpButton.setText(game->str.signUp);
    signUpButton.setVisible(true);
    signUpButton.setEnabled(true);

    demoButton.setText(game->str.demoMode);
    demoButton.setVisible(true);
    demoButton.setEnabled(true);

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);

    displayed = true;
}

void LoginMenu::backFunction() {
    this->hide();
    game->mainMenu.display();
}

void LoginMenu::loginFunction() {
    const int userIndex = loginSelector.currentIndex();
    qDebug() << QCryptographicHash::hash(passwordText.text().toLatin1(), QCryptographicHash::Md5);
    qDebug() << game->users[userIndex].getPasswordHash().toLatin1();
    if (QCryptographicHash::hash(passwordText.text().toLatin1(), QCryptographicHash::Md5) ==
            game->users[userIndex].getPasswordHash()) {
        qDebug() << "Logged in as " << game->users[userIndex].getUsername();
        game->activeUser = userIndex;
        game->activeLocation = 0;
        this->hide();
        game->gameMenu.display();
        game->userTimestamp = QDateTime::currentDateTime();
    } else {
        QMessageBox::warning(game, game->str.fishingTime + ": " + game->str.warning, game->str.incorrectPassword);
    }
    return;
}

void LoginMenu::signUpFunction() {
    this->hide();
    game->signupMenu.display();
}

void LoginMenu::demoFunction() {
    std::uniform_int_distribution<> randomSuffix(0, INT_MAX);
    bool userExists = false;
    QString demoUserName;
    do {
        userExists = false;
        demoUserName = "demo_" + QString::number(randomSuffix(game->randomGenerator));
        for (int i = 0; i < game->users.size(); ++i) {
            if (game->users[i].getUsername() == demoUserName) {
                userExists = true;
                break;
            }
        }
    } while (userExists);
    game->users.push_back(User(demoUserName, ""));
    QMessageBox::warning(game, game->str.fishingTime + ": " + game->str.warning, game->str.demoModeWarning);
    game->activeUser = game->users.size() - 1;
    game->activeLocation = 0;
    this->hide();
    game->gameMenu.display();
}

void LoginMenu::hide() {
    loginSelector.clear();
    loginSelector.setVisible(false);
    loginSelector.setEnabled(false);

    passwordText.setVisible(false);
    passwordText.setEnabled(false);

    loginButton.setVisible(false);
    loginButton.setEnabled(false);

    signUpButton.setVisible(false);
    signUpButton.setEnabled(false);

    demoButton.setVisible(false);
    demoButton.setEnabled(false);

    backButton.setVisible(false);
    backButton.setEnabled(false);

    displayed = false;
}

LoginMenu::~LoginMenu() {
    
}
