#include <random>
#include <QStringList>
#include <QStringList>
#include "gamemenu.h"
#include "game.h"

static std::random_device rd;
static std::mt19937 generator(rd());

GameMenu::GameMenu(Game *game, QGridLayout *grid) :
        game(game),
        grid(grid) {
    table.setRowCount(0);
    table.setColumnCount(2);
    table.setHorizontalHeaderItem(0, &nameWidget);
    table.setHorizontalHeaderItem(1, &quantityWidget);
    table.setVisible(false);
    table.setEnabled(false);

    grid->addWidget(&infoLabel, 0, 0);
    infoLabel.setWordWrap(true);
    infoLabel.setVisible(false);
    infoLabel.setEnabled(false);

    grid->addWidget(&fishLabel, 0, 2);
    fishLabel.setWordWrap(true);
    fishLabel.setVisible(false);
    fishLabel.setEnabled(false);

    grid->addWidget(&clickButton, 2, 1);
    clickButton.setVisible(false);
    clickButton.setEnabled(false);
    connect(&clickButton, SIGNAL(released()), this, SLOT(clickFunction()));

    grid->addWidget(&backButton, 3, 2);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));

    grid->addWidget(&inventoryButton, 3, 0);
    inventoryButton.setVisible(false);
    inventoryButton.setEnabled(false);
    connect(&inventoryButton, SIGNAL(released()), this, SLOT(inventoryFunction()));

    grid->addWidget(&marketButton, 3, 1);
    marketButton.setVisible(false);
    marketButton.setEnabled(false);
    connect(&marketButton, SIGNAL(released()), this, SLOT(marketFunction()));

    grid->addWidget(&storeButton, 2, 0);
    storeButton.setVisible(false);
    storeButton.setEnabled(false);
    connect(&storeButton, SIGNAL(released()), this, SLOT(storeFunction()));

    grid->addWidget(&netsButton, 1, 2);
    netsButton.setVisible(false);
    netsButton.setEnabled(false);
    connect(&netsButton, SIGNAL(released()), this, SLOT(netsFunction()));

    grid->addWidget(&locationSelector, 2, 2);
    locationSelector.setCurrentIndex(0);
    connect(&locationSelector, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
        [this](int index) {
            this->game->activeLocation = index;
            updateInfo();
        });
    locationSelector.setVisible(false);
    locationSelector.setEnabled(false);
}

void GameMenu::display() {
    updateInfo();
    infoLabel.setVisible(true);
    infoLabel.setEnabled(true);

    fishLabel.setVisible(true);
    fishLabel.setEnabled(true);

    nameWidget.setText(game->str.name);
    quantityWidget.setText(game->str.quantity);

    clickButton.setText(game->str.click);
    clickButton.setVisible(true);
    clickButton.setEnabled(true);

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);

    inventoryButton.setText(game->str.inventory);
    inventoryButton.setVisible(true);
    inventoryButton.setEnabled(true);

    marketButton.setText(game->str.market);
    marketButton.setVisible(true);
    marketButton.setEnabled(true);

    storeButton.setText(game->str.store);
    storeButton.setVisible(true);
    storeButton.setEnabled(true);

    netsButton.setText(game->str.nets);
    netsButton.setVisible(true);
    netsButton.setEnabled(true);

    for (int i = 0; i < game->locations.size(); ++i) {
        locationSelector.addItem(game->locations[i].getName());
    }
    locationSelector.setVisible(true);
    locationSelector.setEnabled(true);
}

void GameMenu::clickFunction() {
    const int MOD = 100;
    std::uniform_int_distribution<> dist(1, 99);
    int rnd = dist(generator) % MOD;
    game->users[game->activeUser].inventory.
            changeItem(game->locations[game->activeLocation].getFish(
            qMin(rnd / (MOD / game->locations[game->activeLocation].getFishCount()),
            game->locations[game->activeLocation].getFishCount() - 1)), 1);
    game->users[game->activeUser].incClicks();
    updateInfo();
}

void GameMenu::backFunction() {
    game->activeUser = -1;
    game->activeLocation = -1;
    this->hide();
    game->mainMenu.display();
}

void GameMenu::inventoryFunction() {
    updateInfo();
    table.setVisible(true);
    table.setEnabled(true);
}

void GameMenu::marketFunction() {
    this->hide();
    game->marketMenu.display();
}

void GameMenu::storeFunction() {
    this->hide();
    game->storeMenu.display();
}

void GameMenu::netsFunction() {
    this->hide();
    game->netsMenu.display();
}

void GameMenu::updateInventoryTable() {
    auto inv = game->users[game->activeUser].inventory.get();
    table.setRowCount(inv.size());
    QMap<QString, int>::const_iterator it = inv.constBegin();
    int i = 0;
    while (it != inv.constEnd()) {
        QTableWidgetItem *cell = table.item(i, 0);
        if (!cell) {
            cell = new QTableWidgetItem;
            table.setItem(i, 0, cell);
        }
        cell->setText(game->str.getItemName(it.key()));
        cell->setFlags(cell->flags() & (~Qt::ItemIsEditable));
        cell = table.item(i, 1);
        if (!cell) {
            cell = new QTableWidgetItem;
            table.setItem(i, 1, cell);
        }
        cell->setText(QString::number(it.value()));
        cell->setFlags(cell->flags() & (~Qt::ItemIsEditable));
        ++it;
        ++i;
    }
}

void GameMenu::updateInfo() {
    if (game->activeUser != -1) {
        updateInventoryTable();
        infoLabel.setText(game->str.mainLabelText.arg(
            game->users[game->activeUser].getUsername(),
            QString::number(game->users[game->activeUser].getCoins()),
            QString::number(game->users[game->activeUser].getClicks())
        ));
    }
    if (game->activeLocation != -1) {
        QStringList fishList;
        for (int i = 0; i < game->locations[game->activeLocation].getFishCount(); ++i) {
            fishList.push_back(
                game->str.getItemName(game->locations[game->activeLocation].getFish(i)));
        }
        fishLabel.setText(game->str.fishLabelText.arg(
            game->locations[game->activeLocation].getName(),
            fishList.join(", ")
        ));
    }
}

void GameMenu::hide() {
    infoLabel.setVisible(false);

    fishLabel.setVisible(false);

    clickButton.setVisible(false);
    clickButton.setEnabled(false);

    backButton.setVisible(false);
    backButton.setEnabled(false);

    inventoryButton.setVisible(false);
    inventoryButton.setEnabled(false);

    marketButton.setVisible(false);
    marketButton.setEnabled(false);

    storeButton.setVisible(false);
    storeButton.setEnabled(false);

    netsButton.setVisible(false);
    netsButton.setEnabled(false);

    locationSelector.clear();
    locationSelector.setVisible(false);
    locationSelector.setEnabled(false);
}

GameMenu::~GameMenu() {
    for (int i = 0; ; ++i) {
        int cnt = 0;
        for (int j = 0; j < 2; ++j) {
            if (table.item(i, j)) {
                ++cnt;
                delete table.item(i, j);
            }
        }
        if (!cnt) {
            break;
        }
    }
}
