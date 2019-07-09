#include <random>
#include "gamemenu.h"
#include "mainwindow.h"

static std::random_device rd;
static std::mt19937 generator(rd());

GameMenu::GameMenu(MainWindow *w, QGridLayout *g) :
        window(w),
        grid(g) {
    table.setRowCount(0);
    table.setColumnCount(2);
    table.setHorizontalHeaderItem(0, &nameWidget);
    table.setHorizontalHeaderItem(1, &quantityWidget);
    table.setVisible(false);

    grid->addWidget(&infoLabel, 0, 0);
    infoLabel.setVisible(false);

    grid->addWidget(&clickButton, 1, 1);
    clickButton.setVisible(false);
    connect(&clickButton, SIGNAL(released()), this, SLOT(clickFunction()));

    grid->addWidget(&backButton, 2, 2);
    backButton.setVisible(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));

    grid->addWidget(&inventoryButton, 2, 0);
    inventoryButton.setVisible(false);
    connect(&inventoryButton, SIGNAL(released()), this, SLOT(inventoryFunction()));

    grid->addWidget(&marketButton, 2, 1);
    marketButton.setVisible(false);
    connect(&marketButton, SIGNAL(released()), this, SLOT(marketFunction()));
}

void GameMenu::display() {
    updateInfo();
    infoLabel.setVisible(true);

    clickButton.setText(window->str.click);
    clickButton.setVisible(true);

    backButton.setText(window->str.back);
    backButton.setVisible(true);

    inventoryButton.setText(window->str.inventory);
    inventoryButton.setVisible(true);

    marketButton.setText(window->str.market);
    marketButton.setVisible(true);
}

void GameMenu::clickFunction() {
    const int MOD = 100;
    std::uniform_int_distribution<> dist(1, 99);
    int rnd = dist(generator) % MOD;
    window->users[window->activeUser].inventory.
            changeItem(window->locations[window->activeLocation].getFish(qMin(rnd / (MOD / 3), 2)), 1);
    window->users[window->activeUser].incClicks();
    updateInfo();
}

void GameMenu::backFunction() {
    window->activeUser = -1;
    window->activeLocation = -1;
    this->hide();
    window->mainMenu.display();
}

void GameMenu::inventoryFunction() {
    updateInfo();
    table.setVisible(true);
}

void GameMenu::marketFunction() {
    this->hide();
    window->marketMenu.display();
}

void GameMenu::updateInventoryTable() {
    auto inv = window->users[window->activeUser].inventory.get();
    table.setRowCount(inv.size());
    QMap<QString, int>::const_iterator it = inv.constBegin();
    int i = 0;
    while (it != inv.constEnd()) {
        QTableWidgetItem *cell = table.item(i, 0);
        if (!cell) {
            cell = new QTableWidgetItem;
            table.setItem(i, 0, cell);
        }
        cell->setText(window->str.getItemName(it.key()));
        cell = table.item(i, 1);
        if (!cell) {
            cell = new QTableWidgetItem;
            table.setItem(i, 1, cell);
        }
        cell->setText(QString::number(it.value()));
        ++it;
        ++i;
    }
}

void GameMenu::updateInfo() {
    updateInventoryTable();
    infoLabel.setText(window->str.mainLabelText.arg(
        window->users[window->activeUser].getUsername(),
        QString::number(window->users[window->activeUser].getCoins()),
        QString::number(window->users[window->activeUser].getClicks())
    ));
}

void GameMenu::hide() {
    infoLabel.setVisible(false);
    clickButton.setVisible(false);
    backButton.setVisible(false);
    inventoryButton.setVisible(false);
    marketButton.setVisible(false);
}

GameMenu::~GameMenu() {

}
