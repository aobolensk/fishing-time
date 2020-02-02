#include <QHeaderView>
#include <QMessageBox>
#include "storemenu.h"
#include "game.h"

StoreMenu::StoreMenu(Game *game, QGridLayout *grid) :
        Menu(game, grid) {
    grid->addWidget(&infoLabel, 1, 2);
    infoLabel.setWordWrap(true);
    infoLabel.setVisible(false);
    infoLabel.setEnabled(false);
    infoLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    grid->addWidget(&backButton, 0, 2);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void StoreMenu::display() {
    this->pre_display();

    updateTable();
    updateInfo();

    infoLabel.setVisible(true);
    infoLabel.setEnabled(true);

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);

    displayed = true;
}


void StoreMenu::addItem(const StoreMenu::Item &item, int &index) {

}

void StoreMenu::updateTable() {
    int index = 0;
    if (game->activeLocation == 0) {
        addItem(Item("fish.pike", 1000), index);
        addItem(Item("net.basic", 1000), index);
    } else if (game->activeLocation == 1) {
        addItem(Item("fish.ide", 1100), index);
    }
}

void StoreMenu::updateInfo() {
    infoLabel.setText(game->str.mainLabelText.arg(
        game->users[game->activeUser].getUsername(),
        QString::number(game->users[game->activeUser].getLevel()),
        QString::number(game->users[game->activeUser].getRemainingForNextLevel()),
        QString::number(game->users[game->activeUser].getNeededForNextLevel()),
        QString::number(game->users[game->activeUser].getCoins()),
        QString::number(game->users[game->activeUser].getClicks())
    ));
    game->gameMenu.getPopUpInventoryTable().updateInventoryTables();
}

void StoreMenu::buyFunction(int index) {
    bool ok;
    int quantity = quantityText[index].text().toInt(&ok, 10);
    if (!ok) {
        QMessageBox::warning(game, game->str.fishingTime + ": " + game->str.warning, game->str.quantityShouldBeANumber);
        return;
    }
    qint64 price = item[index].price;
    qint64 sum = quantity * price;
    if (sum > game->users[game->activeUser].getCoins()) {
        QMessageBox::warning(game, game->str.fishingTime + ": " + game->str.warning, game->str.youDontHaveEnoughCoins);
        return;
    }
    if (quantity < 0) {
        QMessageBox::warning(game, game->str.fishingTime + ": " + game->str.warning, game->str.quantityShouldBeMoreThanZero);
        return;
    }
    game->users[game->activeUser].inventory.changeItem(item[index].id, quantity);
    game->users[game->activeUser].changeCoins(-sum);
    game->users[game->activeUser].inventory.updateStats(
        item[index].id,
        "stats.bought", quantity, &game->str.stats
    );
    game->logger.info("Bought " + QString::number(quantity) + " of " + game->str.getItemName(item[index].id));
    updateInfo();
}

void StoreMenu::backFunction() {
    this->hide();
    game->gameMenu.display();
}

void StoreMenu::hide() {
    this->pre_hide();

    infoLabel.setVisible(false);
    infoLabel.setEnabled(false);

    backButton.setVisible(false);
    backButton.setEnabled(false);

    displayed = false;
}

StoreMenu::~StoreMenu() {

}
