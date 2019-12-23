#include "lotterymenu.h"
#include "game.h"

LotteryMenu::LotteryMenu(Game *game, QGridLayout *grid) :
        Menu(game, grid) {
    grid->addWidget(&backButton, 2, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void LotteryMenu::display() {
    this->pre_display();

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);

    displayed = true;
}

void LotteryMenu::backFunction() {
    this->hide();
    game->marketMenu.display();
}

void LotteryMenu::hide() {
    this->pre_hide();

    backButton.setVisible(false);
    backButton.setEnabled(false);

    displayed = false;
}

LotteryMenu::~LotteryMenu() {

}
