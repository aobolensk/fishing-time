#include <random>
#include <QStringList>
#include <QStringList>
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
    table.setEnabled(false);

    grid->addWidget(&infoLabel, 0, 0);
    infoLabel.setWordWrap(true);
    infoLabel.setVisible(false);
    infoLabel.setEnabled(false);

    grid->addWidget(&fishLabel, 0, 2);
    fishLabel.setWordWrap(true);
    fishLabel.setVisible(false);
    fishLabel.setEnabled(false);

    grid->addWidget(&clickButton, 1, 1);
    clickButton.setVisible(false);
    clickButton.setEnabled(false);
    connect(&clickButton, SIGNAL(released()), this, SLOT(clickFunction()));

    grid->addWidget(&backButton, 2, 2);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));

    grid->addWidget(&inventoryButton, 2, 0);
    inventoryButton.setVisible(false);
    inventoryButton.setEnabled(false);
    connect(&inventoryButton, SIGNAL(released()), this, SLOT(inventoryFunction()));

    grid->addWidget(&marketButton, 2, 1);
    marketButton.setVisible(false);
    marketButton.setEnabled(false);
    connect(&marketButton, SIGNAL(released()), this, SLOT(marketFunction()));

    grid->addWidget(&storeButton, 1, 0);
    storeButton.setVisible(false);
    storeButton.setEnabled(false);
    connect(&storeButton, SIGNAL(released()), this, SLOT(storeFunction()));

    grid->addWidget(&locationSelector, 1, 2);
    locationSelector.setCurrentIndex(0);
    connect(&locationSelector, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
        [this](int index) {
            window->activeLocation = index;
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

    nameWidget.setText(window->str.name);
    quantityWidget.setText(window->str.quantity);

    clickButton.setText(window->str.click);
    clickButton.setVisible(true);
    clickButton.setEnabled(true);

    backButton.setText(window->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);

    inventoryButton.setText(window->str.inventory);
    inventoryButton.setVisible(true);
    inventoryButton.setEnabled(true);

    marketButton.setText(window->str.market);
    marketButton.setVisible(true);
    marketButton.setEnabled(true);

    storeButton.setText(window->str.store);
    storeButton.setVisible(true);
    storeButton.setEnabled(true);

    for (int i = 0; i < window->locations.size(); ++i) {
        locationSelector.addItem(window->locations[i].getName());
    }
    locationSelector.setVisible(true);
    locationSelector.setEnabled(true);
}

void GameMenu::clickFunction() {
    const int MOD = 100;
    std::uniform_int_distribution<> dist(1, 99);
    int rnd = dist(generator) % MOD;
    window->users[window->activeUser].inventory.
            changeItem(window->locations[window->activeLocation].getFish(
            qMin(rnd / (MOD / window->locations[window->activeLocation].getFishCount()),
            window->locations[window->activeLocation].getFishCount() - 1)), 1);
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
    table.setEnabled(true);
}

void GameMenu::marketFunction() {
    this->hide();
    window->marketMenu.display();
}

void GameMenu::storeFunction() {
    this->hide();
    window->storeMenu.display();
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
    if (window->activeUser != -1) {
        updateInventoryTable();
        infoLabel.setText(window->str.mainLabelText.arg(
            window->users[window->activeUser].getUsername(),
            QString::number(window->users[window->activeUser].getCoins()),
            QString::number(window->users[window->activeUser].getClicks())
        ));
    }
    if (window->activeLocation != -1) {
        QStringList fishList;
        for (int i = 0; i < window->locations[window->activeLocation].getFishCount(); ++i) {
            fishList.push_back(
                window->str.getItemName(window->locations[window->activeLocation].getFish(i)));
        }
        fishLabel.setText(window->str.fishLabelText.arg(
            window->locations[window->activeLocation].getName(),
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
