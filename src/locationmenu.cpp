#include <random>
#include <QDateTime>
#include <QMessageBox>
#include "gamemenu.h"
#include "game.h"

LocationMenu::LocationMenu(Game *game, QGridLayout *grid) :
        game(game),
        grid(grid) {
    grid->addWidget(&descriptionLabel, 0, 0, 1, 3);
    descriptionLabel.setVisible(false);

    grid->addWidget(&locationSelector, 1, 1);
    locationSelector.setCurrentIndex(0);
    locationSelector.setVisible(false);
    locationSelector.setEnabled(false);

    grid->addWidget(&backButton, 3, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void LocationMenu::display() {
    descriptionLabel.setText(game->str.locationDescription);
    descriptionLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    descriptionLabel.setVisible(true);

    for (int i = 0; i < game->locations.size(); ++i) {
        locationSelector.addItem(game->locations[i].getName());
    }
    locationSelector.setCurrentIndex(game->activeLocation);
    locationUpdater = connect(&locationSelector,
        static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
        [this](int index) {
            if (index == -1)
                return;
            this->game->activeLocation = index;
            qDebug() << "set location:" << this->game->activeLocation;
        });
    locationSelector.setVisible(true);
    locationSelector.setEnabled(true);

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);

    displayed = true;
}

void LocationMenu::backFunction() {
    this->hide();
    game->gameMenu.display();
}

void LocationMenu::hide() {
    descriptionLabel.setVisible(false);

    disconnect(locationUpdater);
    locationSelector.clear();
    locationSelector.setVisible(false);
    locationSelector.setEnabled(false);

    backButton.setVisible(false);
    backButton.setEnabled(false);

    displayed = false;
}

LocationMenu::~LocationMenu() {

}
