#include <random>
#include <QDateTime>
#include <QMessageBox>
#include "gamemenu.h"
#include "mainwindow.h"

MarketMenu::MarketMenu(MainWindow *w, QGridLayout *g) :
        window(w),
        grid(g) {
    grid->addWidget(&infoLabel, 0, 0);
    infoLabel.setVisible(false);
    infoLabel.setEnabled(false);
    for (int i = 0; i < SELLERS_COUNT; ++i) {
        grid->addWidget(&dialogButton[i], 3, i);
        dialogButton[i].setVisible(false);
        dialogButton[i].setEnabled(false);
        grid->addWidget(&dialogLabel[i], 1, i);
        dialogLabel[i].setVisible(false);
        dialogLabel[i].setEnabled(false);
        grid->addWidget(&quantityText[i], 2, i);
        quantityText[i].setText("0");
        quantityText[i].setVisible(false);
        quantityText[i].setEnabled(false);
    }
    #define X(i) connect(&dialogButton[i], &QPushButton::clicked, [this](){processDialog(i);})
    X(0); X(1); X(2);
    #undef X
    grid->addWidget(&backButton, 4, 2);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void MarketMenu::updateDeals() {
    int seed = QDateTime::currentDateTime().daysTo(QDateTime(QDate(2019, 1, 1), QTime(0, 0)));
    std::mt19937 randGen(seed);
    qDebug() << "Random seed:" << seed;
    std::uniform_int_distribution<> gen(0, window->str.itemIds.size() - 1); 
    for (int i = 0; i < SELLERS_COUNT; ++i) {
        goodId[i] = window->str.itemIds[gen(randGen)];
        goodPrice[i] = randGen() % 100;
    }
}

void MarketMenu::updateInfo() {
    infoLabel.setText(window->str.mainLabelText.arg(
        window->users[window->activeUser].getUsername(),
        QString::number(window->users[window->activeUser].getCoins()),
        QString::number(window->users[window->activeUser].getClicks())
    ));
    for (int i = 0; i < SELLERS_COUNT; ++i) {
        dialogLabel[i].setText(
            window->str.sellerText.arg(
                QString::number(i),
                window->str.getItemName(goodId[i]),
                QString::number(goodPrice[i]),
                QString::number(window->users[window->activeUser].inventory.getItem(goodId[i]))
            ));
    }
    window->gameMenu.updateInventoryTable();
}

void MarketMenu::processDialog(int seller) {
    qDebug() << "Processing dialog for seller" << seller;
    bool ok;
    int quantity = quantityText[seller].text().toInt(&ok, 10);
    if (!ok) {
        QMessageBox::warning(window, window->str.warning, window->str.quantityShouldBeANumber);
        return;
    }
    if (quantity > window->users[window->activeUser].inventory.getItem(goodId[seller])) {
        QMessageBox::warning(window, window->str.warning, window->str.youDontHaveEnoughItems);
        return;
    }
    if (quantity < 0) {
        QMessageBox::warning(window, window->str.warning, window->str.quantityShouldBeMoreThanZero);
        return;
    }
    window->users[window->activeUser].inventory.changeItem(goodId[seller], -quantity);
    window->users[window->activeUser].changeCoins(goodPrice[seller] * quantity);
    qDebug() << "Sold" << quantity << "of" << goodId[seller] << "to seller" << seller;
    qDebug() << "Earned" << goodPrice[seller] * quantity << "coins";
    updateInfo();
}

void MarketMenu::display() {
    updateDeals();
    updateInfo();
    infoLabel.setVisible(true);
    infoLabel.setEnabled(true);
    for (int i = 0; i < SELLERS_COUNT; ++i) {
        dialogButton[i].setText(window->str.dialog);
        dialogButton[i].setVisible(true);
        dialogButton[i].setEnabled(true);
        dialogLabel[i].setVisible(true);
        dialogLabel[i].setEnabled(true);
        quantityText[i].setVisible(true);
        quantityText[i].setEnabled(true);
    }
    backButton.setText(window->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);
}

void MarketMenu::backFunction() {
    this->hide();
    window->gameMenu.display();
}

void MarketMenu::hide() {
    infoLabel.setVisible(false);
    infoLabel.setEnabled(false);
    for (int i = 0; i < SELLERS_COUNT; ++i) {
        dialogButton[i].setVisible(false);
        dialogButton[i].setEnabled(false);
        dialogLabel[i].setVisible(false);
        dialogLabel[i].setEnabled(false);
        quantityText[i].setVisible(false);
        quantityText[i].setEnabled(false);
    }
    backButton.setVisible(false);
    backButton.setEnabled(false);
}

MarketMenu::~MarketMenu() {

}
