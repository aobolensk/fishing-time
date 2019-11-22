#include <QHeaderView>
#include "popupinventorymenu.h"
#include "game.h"

PopUpInventoryMenu::PopUpInventoryMenu(Game *game) :
        Menu(game, nullptr, true),
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

void PopUpInventoryMenu::updateInventoryTables() {
    fishTable.setRowCount(0);
    othersTable.setRowCount(0);
    auto inv = game->users[game->activeUser].inventory.get();
    QMap<QString, int>::const_iterator it = inv.constBegin();
    int fishTableIndex = 0;
    int othersTableIndex = 0;
    int *i;
    while (it != inv.constEnd()) {
        QTableWidget *table;
        if (it.key().startsWith("fish.")) {
            table = &fishTable;
            i = &fishTableIndex;
        } else {
            table = &othersTable;
            i = &othersTableIndex;
        }
        table->setRowCount(table->rowCount() + 1);
        QTableWidgetItem *cell = table->item(*i, 0);
        if (!cell) {
            cell = new QTableWidgetItem;
            table->setItem(*i, 0, cell);
        }
        cell->setText(game->str.getItemName(it.key()));
        cell->setFlags(cell->flags() & (~Qt::ItemIsEditable));
        cell = table->item(*i, 1);
        if (!cell) {
            cell = new QTableWidgetItem;
            table->setItem(*i, 1, cell);
        }
        cell->setText(QString::number(it.value()));
        cell->setFlags(cell->flags() & (~Qt::ItemIsEditable));
        ++it;
        ++(*i);
    }
}

void PopUpInventoryMenu::display() {
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

    othersTable.horizontalHeader()->setFont(game->font());
    othersTable.setVisible(true);
    othersTable.setEnabled(true);

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);

    displayed = true;
}

void PopUpInventoryMenu::backFunction() {
    this->hide();
    game->gameMenu.display();
}

void PopUpInventoryMenu::hide() {
    this->pre_hide();

    descriptionLabel.setVisible(false);

    fishTable.setVisible(false);
    fishTable.setEnabled(false);

    othersTable.setVisible(false);
    othersTable.setEnabled(false);

    backButton.setVisible(false);
    backButton.setEnabled(false);

    displayed = false;
}

PopUpInventoryMenu::~PopUpInventoryMenu() {
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
    for (int i = 0; ; ++i) {
        int cnt = 0;
        for (int j = 0; j < 2; ++j) {
            if (othersTable.item(i, j)) {
                ++cnt;
                delete othersTable.item(i, j);
            }
        }
        if (!cnt) {
            break;
        }
    }
}
