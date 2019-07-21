#include <QRegExp>
#include "netsmenu.h"
#include "game.h"

NetsMenu::NetsMenu(Game *game, QGridLayout *grid) :
        game(game),
        grid(grid) {
    grid->addWidget(&netsDescription, 0, 0, 1, SLOTS_COUNT);
    netsDescription.setVisible(false);

    for (int i = 0; i < SLOTS_COUNT; ++i) {
        grid->addWidget(&netSlotLabel[i], 1 + (i / 3) * 2, i % 3);
        netSlotLabel[i].setVisible(false);

        grid->addWidget(&netSlot[i], 2 + (i / 3) * 2, i % 3);
        netSlot[i].setVisible(false);
        netSlot[i].setEnabled(false);
    }

    grid->addWidget(&backButton, 3 + SLOTS_COUNT / 3 * 2, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void NetsMenu::updateNets() {
    const QMap<QString, int> &inv = game->users[game->activeUser].inventory.get();
    auto it = inv.begin();
    for (int i = 0; i < SLOTS_COUNT; ++i) {
        netSlot[i].addItem(game->str.empty);
    }
    while (it != inv.end()) {
        if (QRegExp("net.*").exactMatch(it.key())) {
            for (int i = 0; i < SLOTS_COUNT; ++i) {
                netSlot[i].addItem(it.key() + " (" + QString::number(it.value()) + ')');
            }
        }
        ++it;
    }
}

void NetsMenu::display() {
    updateNets();

    netsDescription.setText(game->str.netsDescription);
    netsDescription.setVisible(true);

    for (int i = 0; i < SLOTS_COUNT; ++i) {
        netSlotLabel[i].setText(game->str.netSlot.arg(i));
        netSlotLabel[i].setVisible(true);

        netSlot[i].setVisible(true);
        netSlot[i].setEnabled(true);
    }

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);
}

void NetsMenu::backFunction() {
    this->hide();
    game->gameMenu.display();
}

void NetsMenu::hide() {
    netsDescription.setVisible(false);

    for (int i = 0; i < SLOTS_COUNT; ++i) {
        netSlotLabel[i].setVisible(false);

        netSlot[i].setVisible(false);
        netSlot[i].setEnabled(false);
    }

    backButton.setVisible(false);
    backButton.setEnabled(false);
}

NetsMenu::~NetsMenu() {

}
