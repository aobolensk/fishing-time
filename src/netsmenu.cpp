#include "netsmenu.h"
#include "game.h"

NetsMenu::NetsMenu(Game *game, QGridLayout *grid) :
        game(game),
        grid(grid) {
    grid->addWidget(&backButton, 2, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void NetsMenu::display() {
    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);
}

void NetsMenu::backFunction() {
    this->hide();
    game->gameMenu.display();
}

void NetsMenu::hide() {
    backButton.setVisible(false);
    backButton.setEnabled(false);
}

NetsMenu::~NetsMenu() {

}
