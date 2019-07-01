#include "gamemenu.h"
#include "mainwindow.h"

GameMenu::GameMenu(MainWindow *w, QGridLayout *g) :
        window(w),
        clickButton(QPushButton(window)),
        backButton(QPushButton(window)),
        infoLabel(QLabel(window)),
        grid(g) {
    grid->addWidget(&infoLabel, 0, 0);
    infoLabel.setVisible(false);
    grid->addWidget(&clickButton, 1, 1);
    clickButton.setVisible(false);
    grid->addWidget(&backButton, 1, 2);
    backButton.setVisible(false);
}

void GameMenu::display() {
    updateInfo();
    infoLabel.setVisible(true);
    clickButton.setText("Click");
    clickButton.setVisible(true);
    connect(&clickButton, SIGNAL(released()), this, SLOT(clickFunction()));
    backButton.setText("Back");
    backButton.setVisible(true);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void GameMenu::clickFunction() {
    window->users[window->activeUser].incClicks();
    updateInfo();
}

void GameMenu::backFunction() {
    window->activeUser = -1;
    this->hide();
    window->mainMenu.display();
}

void GameMenu::updateInfo() {
    QString s;
    s += "Welcome, " + window->users[window->activeUser].getUsername() + '\n';
    s += "Clicks: " + QString::number(window->users[window->activeUser].getClicks()) + '\n';
    infoLabel.setText(s);
}

void GameMenu::hide() {
    infoLabel.setVisible(false);
    clickButton.setVisible(false);
    disconnect(&clickButton, SIGNAL(released()), this, SLOT(clickFunction()));
    backButton.setVisible(false);
    disconnect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

GameMenu::~GameMenu() {

}
