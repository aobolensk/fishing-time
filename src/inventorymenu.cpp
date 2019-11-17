#include <QHeaderView>
#include "inventorymenu.h"
#include "game.h"

InventoryMenu::InventoryMenu(Game *game, QGridLayout *grid) :
        Menu(game, grid),
        fishTable(game),
        othersTable(game) {
    grid->addWidget(&descriptionLabel, 0, 1);
    descriptionLabel.setVisible(false);
    descriptionLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    grid->addWidget(&fishTable, 1, 0, 1, 3);
    fishTable.setRowCount(0);
    fishTable.setColumnCount(2);
    fishTable.setSelectionMode(QAbstractItemView::NoSelection);
    fishTable.verticalHeader()->setVisible(false);
    fishTable.setHorizontalHeaderItem(0, &fishNameHeader);
    fishTable.setHorizontalHeaderItem(1, &fishQuantityHeader);
    fishTable.setVisible(false);
    fishTable.setEnabled(false);
    fishTable.horizontalHeader()->setStretchLastSection(true);

    grid->addWidget(&othersTable, 2, 0, 1, 3);
    othersTable.setRowCount(0);
    othersTable.setColumnCount(2);
    othersTable.setSelectionMode(QAbstractItemView::NoSelection);
    othersTable.verticalHeader()->setVisible(false);
    othersTable.setHorizontalHeaderItem(0, &othersNameHeader);
    othersTable.setHorizontalHeaderItem(1, &othersQuantityHeader);
    othersTable.setVisible(false);
    othersTable.setEnabled(false);
    othersTable.horizontalHeader()->setStretchLastSection(true);

    grid->addWidget(&backButton, 3, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void InventoryMenu::updateInventoryTables() {
    auto inv = game->users[game->activeUser].inventory.get();
    QMap<QString, int>::const_iterator it = inv.constBegin();
    int i = 0;
    while (it != inv.constEnd()) {
        QTableWidget *table;
        table = &fishTable;
        table->setRowCount(table->rowCount() + 1);
        QTableWidgetItem *cell = table->item(i, 0);
        if (!cell) {
            cell = new QTableWidgetItem;
            table->setItem(i, 0, cell);
        }
        cell->setText(game->str.getItemName(it.key()));
        cell->setFlags(cell->flags() & (~Qt::ItemIsEditable));
        cell = table->item(i, 1);
        if (!cell) {
            cell = new QTableWidgetItem;
            table->setItem(i, 1, cell);
        }
        cell->setText(QString::number(it.value()));
        cell->setFlags(cell->flags() & (~Qt::ItemIsEditable));
        ++it;
        ++i;
    }
}

void InventoryMenu::display() {
    this->pre_display();

    updateInventoryTables();

    descriptionLabel.setVisible(true);
    descriptionLabel.setText(game->str.inventoryDescription.arg(
        game->users[game->activeUser].getUsername()
    ));

    fishNameHeader.setText(game->str.name);
    fishQuantityHeader.setText(game->str.quantity);
    othersNameHeader.setText(game->str.name);
    othersQuantityHeader.setText(game->str.quantity);

    fishTable.horizontalHeader()->setFont(game->font());
    fishTable.setVisible(true);
    fishTable.setEnabled(true);

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);

    displayed = true;
}

void InventoryMenu::backFunction() {
    this->hide();
    game->gameMenu.display();
}

void InventoryMenu::hide() {
    this->pre_hide();

    descriptionLabel.setVisible(false);

    fishTable.setVisible(false);
    fishTable.setEnabled(false);

    backButton.setVisible(false);
    backButton.setEnabled(false);

    displayed = false;
}

InventoryMenu::~InventoryMenu() {
    for (int i = 0; ; ++i) {
        int cnt = 0;
        for (int j = 0; j < 2; ++j) {
            if (fishTable.item(i, j)) {
                ++cnt;
                delete fishTable.item(i, j);
            }
        }
        if (!cnt) {
            break;
        }
    }
}
