#include "controlsmenu.h"
#include "game.h"

ControlsMenu::ControlsMenu(Game *game, QGridLayout *grid) :
        Menu(game, grid) {
    grid->addWidget(&backButton, 2, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void ControlsMenu::display() {
    this->pre_display();

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);

    displayed = true;
}

void ControlsMenu::backFunction() {
    this->hide();
    game->settingsMenu.display();
}

void ControlsMenu::hide() {
    this->pre_hide();

    backButton.setVisible(false);
    backButton.setEnabled(false);

    displayed = false;
}

ControlsMenu::~ControlsMenu() {

}
