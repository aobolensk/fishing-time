#include <random>
#include "gamemenu.h"
#include "mainwindow.h"

MarketMenu::MarketMenu(MainWindow *w, QGridLayout *g) :
        window(w),
        backButton(QPushButton(window)),
        grid(g) {
    grid->addWidget(&backButton, 1, 2);
    backButton.setVisible(false);
}

void MarketMenu::display() {
    backButton.setText(window->str.back);
    backButton.setVisible(true);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void MarketMenu::backFunction() {
    this->hide();
    window->gameMenu.display();
}

void MarketMenu::hide() {
    backButton.setVisible(false);
    disconnect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

MarketMenu::~MarketMenu() {

}
