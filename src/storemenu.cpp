#include <QMessageBox>
#include "storemenu.h"
#include "mainwindow.h"

StoreMenu::StoreMenu(MainWindow *w, QGridLayout *g) :
        window(w),
        storeTable(window),
        grid(g) {
    grid->addWidget(&infoLabel, 1, 2);
    infoLabel.setVisible(false);

    grid->addWidget(&storeTable, 1, 0, 1, 2);
    storeTable.setRowCount(0);
    storeTable.setColumnCount(3);
    storeTable.setVisible(false);

    grid->addWidget(&quantityText, 0, 0);
    quantityText.setText("0");
    quantityText.setVisible(false);

    grid->addWidget(&buyButton, 0, 1);
    buyButton.setVisible(false);
    connect(&buyButton, SIGNAL(released()), this, SLOT(buyFunction()));

    grid->addWidget(&backButton, 0, 2);
    backButton.setVisible(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void StoreMenu::display() {
    updateTable();
    updateInfo();
    infoLabel.setVisible(true);
    storeTable.setVisible(true);

    quantityText.setVisible(true);

    buyButton.setText(window->str.buy);
    buyButton.setVisible(true);

    backButton.setText(window->str.back);
    backButton.setVisible(true);
}

void StoreMenu::updateTable() {
    static auto addDeal = [&](int index, const QString &name, const QString &description, qint64 price) {
        QTableWidgetItem *cell = storeTable.item(index, 0);
        if (!cell) {
            cell = new QTableWidgetItem;
            storeTable.setItem(index, 0, cell);
        }
        cell->setText(name);
        cell->setFlags(cell->flags() ^ Qt::ItemIsEditable);
        cell = storeTable.item(index, 1);
        if (!cell) {
            cell = new QTableWidgetItem;
            storeTable.setItem(index, 1, cell);
        }
        cell->setText(description);
        cell->setFlags(cell->flags() ^ Qt::ItemIsEditable);
        cell = storeTable.item(index, 2);
        if (!cell) {
            cell = new QTableWidgetItem;
            storeTable.setItem(index, 2, cell);
        }
        cell->setText(QString::number(price));
        cell->setFlags(cell->flags() ^ Qt::ItemIsEditable);
    };
    storeTable.setRowCount(1);
    addDeal(0, "fish.pike", window->str.pike, 1000);
}

void StoreMenu::updateInfo() {
    infoLabel.setText(window->str.mainLabelText.arg(
        window->users[window->activeUser].getUsername(),
        QString::number(window->users[window->activeUser].getCoins()),
        QString::number(window->users[window->activeUser].getClicks())
    ));
    window->gameMenu.updateInventoryTable();
}

void StoreMenu::buyFunction() {
    if (storeTable.currentRow() == -1) {
        QMessageBox::warning(window, window->str.warning, window->str.selectItemFromList);
        return;
    }
    bool ok;
    int quantity = quantityText.text().toInt(&ok, 10);
    if (!ok) {
        QMessageBox::warning(window, window->str.warning, window->str.quantityShouldBeANumber);
        return;
    }
    qint64 price = storeTable.item(storeTable.currentRow(), 2)->text().toLongLong();
    if (quantity * price > window->users[window->activeUser].getCoins()) {
        QMessageBox::warning(window, window->str.warning, window->str.youDontHaveEnoughCoins);
        return;
    }
    if (quantity < 0) {
        QMessageBox::warning(window, window->str.warning, window->str.quantityShouldBeMoreThanZero);
        return;
    }
    window->users[window->activeUser].inventory.changeItem(storeTable.item(storeTable.currentRow(), 0)->text(), quantity);
    window->users[window->activeUser].changeCoins(-quantity * storeTable.item(storeTable.currentRow(), 2)->text().toLongLong() * quantity);
    qDebug() << "Bought" << quantity << "of" << storeTable.currentRow();
    updateInfo();
}

void StoreMenu::backFunction() {
    this->hide();
    window->gameMenu.display();
}

void StoreMenu::hide() {
    infoLabel.setVisible(false);
    storeTable.setVisible(false);
    quantityText.setVisible(false);
    buyButton.setVisible(false);
    backButton.setVisible(false);
}

StoreMenu::~StoreMenu() {

}
