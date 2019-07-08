#include <random>
#include <QDateTime>
#include "gamemenu.h"
#include "mainwindow.h"

MarketMenu::MarketMenu(MainWindow *w, QGridLayout *g) :
        window(w),
        backButton(QPushButton(window)),
        grid(g) {
    for (int i = 0; i < SELLERS_COUNT; ++i) {
        grid->addWidget(&dialogButton[i], 2, i);
        dialogButton[i].setVisible(false);
        grid->addWidget(&dialogLabel[i], 1, i);
        dialogLabel[i].setVisible(false);
    }

    grid->addWidget(&backButton, 3, 2);
    backButton.setVisible(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void MarketMenu::display() {
    for (int i = 0; i < 3; ++i) {
        dialogButton[i].setText(window->str.dialog);
        dialogButton[i].setVisible(true);
        dialogLabel[i].setText(window->str.dialog);
        dialogLabel[i].setVisible(true);
    }
    backButton.setText(window->str.back);
    backButton.setVisible(true);
}

void MarketMenu::backFunction() {
    this->hide();
    window->gameMenu.display();
}

void MarketMenu::hide() {
    for (int i = 0; i < SELLERS_COUNT; ++i) {
        dialogButton[i].setVisible(false);
        dialogLabel[i].setVisible(false);
    }
    backButton.setVisible(false);
}

MarketMenu::~MarketMenu() {

}
