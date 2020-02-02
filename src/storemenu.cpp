#include <QHeaderView>
#include <QMessageBox>
#include "storemenu.h"
#include "game.h"

StoreMenu::StoreMenu(Game *game, QGridLayout *grid) :
        Menu(game, grid) {
    grid->addWidget(&infoLabel, 0, 2);
    infoLabel.setWordWrap(true);
    infoLabel.setVisible(false);
    infoLabel.setEnabled(false);
    infoLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    infoLabel.setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    for (int i = 0; i < Config::STORE_MAX_ITEMS_COUNT; ++i) {
        grid->addWidget(&itemLabel[i], i + 1, 0);
        itemLabel[i].setVisible(false);
        itemLabel[i].setEnabled(false);

        grid->addWidget(&quantityText[i], i + 1, 1);
        quantityText[i].setVisible(false);
        quantityText[i].setEnabled(false);

        grid->addWidget(&buyButton[i], i + 1, 2);
        buyButton[i].setVisible(false);
        buyButton[i].setEnabled(false);
    }

    grid->addWidget(&backButton, Config::STORE_MAX_ITEMS_COUNT + 2, 1);
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
    itemLabel[index].setText(game->str.getItemName(item.id) + ": " + QString::number(item.price));
    itemLabel[index].setVisible(true);
    itemLabel[index].setEnabled(true);

    quantityText[index].setText("1");
    quantityText[index].setVisible(true);
    quantityText[index].setEnabled(true);

    buyButton[index].setText(game->str.buy);
    buyButton[index].setVisible(true);
    buyButton[index].setEnabled(true);
    itemUpdater[index] = connect(&buyButton[index], &QPushButton::released, [this, index] {
        buyFunction(index);
    });

    ++index;
}

void StoreMenu::clearTable() {
    for (int i = 0; i < Config::STORE_MAX_ITEMS_COUNT; ++i) {
        itemLabel[i].setText("");
        itemLabel[i].setVisible(false);
        itemLabel[i].setEnabled(false);

        quantityText[i].setText("");
        quantityText[i].setVisible(false);
        quantityText[i].setEnabled(false);

        buyButton[i].setText("");
        buyButton[i].setVisible(false);
        buyButton[i].setEnabled(false);
        disconnect(itemUpdater[i]);
    }
}

void StoreMenu::updateTable() {
    int index = 0;
    clearTable();
    if (game->activeLocation == 0) {
        addItem(itemRecord[index] = Item("fish.pike", 1000), index);
        addItem(itemRecord[index] = Item("net.basic", 1000), index);
    } else if (game->activeLocation == 1) {
        addItem(itemRecord[index] = Item("fish.ide", 1100), index);
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
    qDebug() << "Buy" << index;
    bool ok;
    int quantity = quantityText[index].text().toInt(&ok, 10);
    if (!ok) {
        QMessageBox::warning(game, game->str.fishingTime + ": " + game->str.warning, game->str.quantityShouldBeANumber);
        return;
    }
    qint64 price = itemRecord[index].price;
    qint64 sum = quantity * price;
    if (sum > game->users[game->activeUser].getCoins()) {
        QMessageBox::warning(game, game->str.fishingTime + ": " + game->str.warning, game->str.youDontHaveEnoughCoins);
        return;
    }
    if (quantity < 0) {
        QMessageBox::warning(game, game->str.fishingTime + ": " + game->str.warning, game->str.quantityShouldBeMoreThanZero);
        return;
    }
    game->users[game->activeUser].inventory.changeItem(itemRecord[index].id, quantity);
    game->users[game->activeUser].changeCoins(-sum);
    game->users[game->activeUser].inventory.updateStats(
        itemRecord[index].id,
        "stats.bought", quantity, &game->str.stats
    );
    game->logger.info("Bought " + QString::number(quantity) + " of " + game->str.getItemName(itemRecord[index].id));
    updateInfo();
}

void StoreMenu::backFunction() {
    this->hide();
    game->gameMenu.display();
}

void StoreMenu::hide() {
    this->pre_hide();

    clearTable();

    infoLabel.setVisible(false);
    infoLabel.setEnabled(false);

    backButton.setVisible(false);
    backButton.setEnabled(false);

    displayed = false;
}

StoreMenu::~StoreMenu() {

}
