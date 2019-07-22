#include <QMessageBox>
#include "storemenu.h"
#include "game.h"

StoreMenu::StoreMenu(Game *game, QGridLayout *grid) :
        game(game),
        storeTable(game),
        grid(grid) {
    grid->addWidget(&infoLabel, 1, 2);
    infoLabel.setWordWrap(true);
    infoLabel.setVisible(false);
    infoLabel.setEnabled(false);

    grid->addWidget(&storeTable, 1, 0, 1, 2);
    storeTable.setRowCount(0);
    storeTable.setColumnCount(3);
    storeTable.setVisible(false);
    storeTable.setEnabled(false);

    grid->addWidget(&quantityText, 0, 0);
    quantityText.setText("0");
    quantityText.setVisible(false);
    quantityText.setEnabled(false);

    grid->addWidget(&buyButton, 0, 1);
    buyButton.setVisible(false);
    buyButton.setEnabled(false);
    connect(&buyButton, SIGNAL(released()), this, SLOT(buyFunction()));

    grid->addWidget(&backButton, 0, 2);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void StoreMenu::display() {
    updateTable();
    updateInfo();
    infoLabel.setVisible(true);
    infoLabel.setEnabled(true);
    storeTable.setVisible(true);
    storeTable.setEnabled(true);

    quantityText.setVisible(true);
    quantityText.setEnabled(true);

    buyButton.setText(game->str.buy);
    buyButton.setVisible(true);
    buyButton.setEnabled(true);

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);
}

void StoreMenu::updateTable() {
    static auto addDeal = [this](int index, const QString &name, const QString &description, qint64 price) {
        QTableWidgetItem *cell = storeTable.item(index, 0);
        if (!cell) {
            cell = new QTableWidgetItem;
            storeTable.setItem(index, 0, cell);
        }
        cell->setText(name);
        cell->setFlags(cell->flags() & (~Qt::ItemIsEditable));
        cell = storeTable.item(index, 1);
        if (!cell) {
            cell = new QTableWidgetItem;
            storeTable.setItem(index, 1, cell);
        }
        cell->setText(description);
        cell->setFlags(cell->flags() & (~Qt::ItemIsEditable));
        cell = storeTable.item(index, 2);
        if (!cell) {
            cell = new QTableWidgetItem;
            storeTable.setItem(index, 2, cell);
        }
        cell->setText(QString::number(price));
        cell->setFlags(cell->flags() & (~Qt::ItemIsEditable));
    };
    storeTable.setRowCount(2);
    addDeal(0, "fish.pike", game->str.pike, 1000);
    addDeal(1, "net.basic", game->str.basicNet, 1000);
}

void StoreMenu::updateInfo() {
    infoLabel.setText(game->str.mainLabelText.arg(
        game->users[game->activeUser].getUsername(),
        QString::number(game->users[game->activeUser].getCoins()),
        QString::number(game->users[game->activeUser].getClicks())
    ));
    game->gameMenu.updateInventoryTable();
}

void StoreMenu::buyFunction() {
    if (storeTable.currentRow() == -1) {
        QMessageBox::warning(game, game->str.warning, game->str.selectItemFromList);
        return;
    }
    bool ok;
    int quantity = quantityText.text().toInt(&ok, 10);
    if (!ok) {
        QMessageBox::warning(game, game->str.warning, game->str.quantityShouldBeANumber);
        return;
    }
    qint64 price = storeTable.item(storeTable.currentRow(), 2)->text().toLongLong();
    qint64 sum = quantity * price;
    if (sum > game->users[game->activeUser].getCoins()) {
        QMessageBox::warning(game, game->str.warning, game->str.youDontHaveEnoughCoins);
        return;
    }
    if (quantity < 0) {
        QMessageBox::warning(game, game->str.warning, game->str.quantityShouldBeMoreThanZero);
        return;
    }
    game->users[game->activeUser].inventory.changeItem(storeTable.item(storeTable.currentRow(), 0)->text(), quantity);
    game->users[game->activeUser].changeCoins(-sum);
    qDebug() << "Bought" << quantity << "of" << storeTable.currentRow();
    updateInfo();
}

void StoreMenu::backFunction() {
    this->hide();
    game->gameMenu.display();
}

void StoreMenu::hide() {
    infoLabel.setVisible(false);
    infoLabel.setEnabled(false);

    storeTable.setVisible(false);
    storeTable.setEnabled(false);

    quantityText.setVisible(false);
    quantityText.setEnabled(false);

    buyButton.setVisible(false);
    buyButton.setEnabled(false);

    backButton.setVisible(false);
    backButton.setEnabled(false);
}

StoreMenu::~StoreMenu() {
    for (int i = 0; ; ++i) {
        int cnt = 0;
        for (int j = 0; j < 3; ++j) {
            if (storeTable.item(i, j)) {
                ++cnt;
                delete storeTable.item(i, j);
            }
        }
        if (!cnt) {
            break;
        }
    }
}
