#include "statisticsmenu.h"
#include "game.h"

StatisticsMenu::StatisticsMenu(Game *game, QGridLayout *grid) :
        game(game),
        grid(grid) {
    grid->addWidget(&backButton, 0, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void StatisticsMenu::display() {
    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);
}

void StatisticsMenu::backFunction() {
    this->hide();
    game->gameMenu.display();
}

void StatisticsMenu::hide() {
    backButton.setVisible(false);
    backButton.setEnabled(false);
}

StatisticsMenu::~StatisticsMenu() {

}
