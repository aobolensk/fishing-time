#include "creditsmenu.h"
#include "game.h"

CreditsMenu::CreditsMenu(Game *game, QGridLayout *grid) :
        Menu(game, grid) {
    grid->addWidget(&backButton, 2, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void CreditsMenu::display() {
    this->pre_display();

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);

    displayed = true;
}

void CreditsMenu::backFunction() {
    this->hide();
    game->mainMenu.display();
}

void CreditsMenu::hide() {
    this->pre_hide();

    backButton.setVisible(false);
    backButton.setEnabled(false);

    displayed = false;
}

CreditsMenu::~CreditsMenu() {

}
