#include "ratingmenu.h"
#include "game.h"

RatingMenu::RatingMenu(Game *game, QGridLayout *grid) :
        game(game),
        grid(grid) {
    grid->addWidget(&backButton, 2, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void RatingMenu::display() {
    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);
}

void RatingMenu::backFunction() {
    this->hide();
    game->mainMenu.display();
}

void RatingMenu::hide() {
    backButton.setVisible(false);
    backButton.setEnabled(false);
}

RatingMenu::~RatingMenu() {

}
