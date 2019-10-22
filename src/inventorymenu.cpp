#include <QHeaderView>
#include "inventorymenu.h"
#include "game.h"

InventoryMenu::InventoryMenu(Game *game, QGridLayout *grid) :
        game(game),
        inventoryTable(game),
        grid(grid) {
    grid->addWidget(&descriptionLabel, 0, 1);
    descriptionLabel.setVisible(false);
    descriptionLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    grid->addWidget(&inventoryTable, 1, 0, 1, 3);
    inventoryTable.setRowCount(0);
    inventoryTable.setColumnCount(2);
    inventoryTable.setSelectionMode(QAbstractItemView::NoSelection);
    inventoryTable.verticalHeader()->setVisible(false);
    inventoryTable.setHorizontalHeaderItem(0, &nameHeader);
    inventoryTable.setHorizontalHeaderItem(1, &quantityHeader);
    inventoryTable.setVisible(false);
    inventoryTable.setEnabled(false);
    inventoryTable.horizontalHeader()->setStretchLastSection(true);

    grid->addWidget(&backButton, 2, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void InventoryMenu::updateInventoryTable() {
    auto inv = game->users[game->activeUser].inventory.get();
    inventoryTable.setRowCount(inv.size());
    QMap<QString, int>::const_iterator it = inv.constBegin();
    int i = 0;
    while (it != inv.constEnd()) {
        QTableWidgetItem *cell = inventoryTable.item(i, 0);
        if (!cell) {
            cell = new QTableWidgetItem;
            inventoryTable.setItem(i, 0, cell);
        }
        cell->setText(game->str.getItemName(it.key()));
        cell->setFlags(cell->flags() & (~Qt::ItemIsEditable));
        cell = inventoryTable.item(i, 1);
        if (!cell) {
            cell = new QTableWidgetItem;
            inventoryTable.setItem(i, 1, cell);
        }
        cell->setText(QString::number(it.value()));
        cell->setFlags(cell->flags() & (~Qt::ItemIsEditable));
        ++it;
        ++i;
    }
}

bool InventoryMenu::isDisplayed() const {
    return displayed;
}

void InventoryMenu::display() {
    updateInventoryTable();

    descriptionLabel.setVisible(true);
    descriptionLabel.setText(game->str.inventoryDescription.arg(
        game->users[game->activeUser].getUsername()
    ));

    nameHeader.setText(game->str.name);
    quantityHeader.setText(game->str.quantity);

    inventoryTable.horizontalHeader()->setFont(game->font());
    inventoryTable.setVisible(true);
    inventoryTable.setEnabled(true);

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
    descriptionLabel.setVisible(false);

    inventoryTable.setVisible(false);
    inventoryTable.setEnabled(false);

    backButton.setVisible(false);
    backButton.setEnabled(false);

    displayed = false;
}

InventoryMenu::~InventoryMenu() {
    for (int i = 0; ; ++i) {
        int cnt = 0;
        for (int j = 0; j < 2; ++j) {
            if (inventoryTable.item(i, j)) {
                ++cnt;
                delete inventoryTable.item(i, j);
            }
        }
        if (!cnt) {
            break;
        }
    }
}
