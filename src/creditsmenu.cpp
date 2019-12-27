#include "creditsmenu.h"
#include "game.h"

CreditsMenu::CreditsMenu(Game *game, QGridLayout *grid) :
        Menu(game, grid) {
    grid->addWidget(&creditsLabel, 0, 1);
    creditsLabel.setVisible(false);
    creditsLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    creditsLabel.setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    grid->addWidget(&contributorsListLabel, 1, 1);
    contributorsListLabel.setVisible(false);

    grid->addWidget(&backButton, 2, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void CreditsMenu::display() {
    this->pre_display();

    creditsLabel.setText(game->str.credits);
    creditsLabel.setVisible(true);

    contributorsListLabel.setText(
        "Contributors:\n\n"
        "gooddoog\n"
        "Abrams19\n"
    );
    contributorsListLabel.setVisible(true);

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

    creditsLabel.setVisible(false);

    contributorsListLabel.setVisible(false);

    backButton.setVisible(false);
    backButton.setEnabled(false);

    displayed = false;
}

CreditsMenu::~CreditsMenu() {

}
