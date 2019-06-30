#include <QCoreApplication>
#include "mainmenu.h"

MainMenu::MainMenu(QWidget *w, QGridLayout *g) :
        window(w),
        clickButton(QPushButton(window)),
        exitButton(QPushButton(window)),
        grid(g) {
    grid->addWidget(&clickButton, 0, 0);
    grid->addWidget(&exitButton, 1, 0);
    clickButton.setVisible(false);
    exitButton.setVisible(false);
}

void MainMenu::display() {
    clickButton.setText("Click");
    clickButton.setVisible(true);
    connect(&clickButton, SIGNAL(released()), this, SLOT(clickFunction()));
    exitButton.setText("Exit");
    exitButton.setVisible(true);
    connect(&exitButton, SIGNAL(released()), this, SLOT(exitFunction()));
}

void MainMenu::clickFunction() {
    clickButton.setText(QString::number(++cnt));
}

void MainMenu::exitFunction() {
    this->hide();
}

void MainMenu::hide() {
    clickButton.setVisible(false);
    disconnect(&clickButton, SIGNAL(released()), this, SLOT(clickFunction()));
    exitButton.setVisible(false);
    disconnect(&exitButton, SIGNAL(released()), this, SLOT(exitFunction()));
}

MainMenu::~MainMenu() {
    
}
