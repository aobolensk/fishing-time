#include "aboutmenu.h"
#include "game.h"

AboutMenu::AboutMenu(Game *game) :
        game(game) {
    this->setLayout(&grid);

    grid.addWidget(&descriptionLabel, 0, 0, 1, 3);
    descriptionLabel.setVisible(false);
    descriptionLabel.setWordWrap(true);

    grid.addWidget(&backButton, 1, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void AboutMenu::display() {
    this->setVisible(true);

    descriptionLabel.setText(game->str.aboutDescription);
    descriptionLabel.setVisible(true);

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);
}

void AboutMenu::backFunction() {
    this->hide();

    this->setVisible(false);
}

void AboutMenu::hide() {
    descriptionLabel.setVisible(false);

    backButton.setVisible(false);
    backButton.setEnabled(false);
}

AboutMenu::~AboutMenu() {

}
