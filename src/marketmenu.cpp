#include <random>
#include <QDateTime>
#include <QMessageBox>
#include "gamemenu.h"
#include "game.h"

MarketMenu::MarketMenu(Game *game, QGridLayout *grid) :
        game(game),
        grid(grid) {
    grid->addWidget(&descriptionLabel, 0, 0, 1, 2);
    descriptionLabel.setVisible(false);
    descriptionLabel.setEnabled(false);
    descriptionLabel.setWordWrap(true);

    grid->addWidget(&infoLabel, 0, 2);
    infoLabel.setVisible(false);
    infoLabel.setEnabled(false);
    infoLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    for (int i = 0; i < SELLERS_COUNT; ++i) {
        grid->addWidget(&dialogButton[i], 3, i);
        dialogButton[i].setVisible(false);
        dialogButton[i].setEnabled(false);
        grid->addWidget(&dialogLabel[i], 1, i);
        dialogLabel[i].setWordWrap(true);
        dialogLabel[i].setVisible(false);
        dialogLabel[i].setEnabled(false);
        dialogLabel[i].setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
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
    std::uniform_int_distribution<> gen(0, game->str.itemIds.size() - 2);
    for (int i = 0; i < SELLERS_COUNT; ++i) {
        goodId[i] = game->str.itemIds[gen(randGen)];
        goodPrice[i] = randGen() % 100;
    }
}

void MarketMenu::updateInfo() {
    infoLabel.setText(game->str.mainLabelText.arg(
        game->users[game->activeUser].getUsername(),
        QString::number(game->users[game->activeUser].getCoins()),
        QString::number(game->users[game->activeUser].getClicks())
    ));

    for (int i = 0; i < SELLERS_COUNT; ++i) {
        dialogLabel[i].setText(
            game->str.sellerText.arg(
                QString::number(i),
                game->str.getItemName(goodId[i]),
                QString::number(goodPrice[i]),
                QString::number(game->users[game->activeUser].inventory.getItem(goodId[i]))
            ));
    }
    game->gameMenu.updateInventoryTable();
}

void MarketMenu::processDialog(int seller) {
    qDebug() << "Processing dialog for seller" << seller;
    bool ok;
    int quantity = quantityText[seller].text().toInt(&ok, 10);
    if (!ok) {
        QMessageBox::warning(game, game->str.fishingTime + ": " + game->str.warning, game->str.quantityShouldBeANumber);
        return;
    }
    if (quantity > game->users[game->activeUser].inventory.getItem(goodId[seller])) {
        QMessageBox::warning(game, game->str.fishingTime + ": " + game->str.warning, game->str.youDontHaveEnoughItems);
        return;
    }
    if (quantity < 0) {
        QMessageBox::warning(game, game->str.fishingTime + ": " + game->str.warning, game->str.quantityShouldBeMoreThanZero);
        return;
    }
    game->users[game->activeUser].inventory.changeItem(goodId[seller], -quantity);
    game->users[game->activeUser].changeCoins(goodPrice[seller] * quantity);
    qDebug() << "Sold" << quantity << "of" << goodId[seller] << "to seller" << seller;
    qDebug() << "Earned" << goodPrice[seller] * quantity << "coins";
    updateInfo();
}

bool MarketMenu::isDisplayed() const {
    return displayed;
}

void MarketMenu::display() {
    updateDeals();
    updateInfo();

    descriptionLabel.setText(game->str.marketDescription);
    descriptionLabel.setVisible(true);
    descriptionLabel.setEnabled(true);

    infoLabel.setVisible(true);
    infoLabel.setEnabled(true);

    for (int i = 0; i < SELLERS_COUNT; ++i) {
        dialogButton[i].setText(game->str.dialog);
        dialogButton[i].setVisible(true);
        dialogButton[i].setEnabled(true);

        dialogLabel[i].setVisible(true);
        dialogLabel[i].setEnabled(true);

        quantityText[i].setVisible(true);
        quantityText[i].setEnabled(true);
    }

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);

    displayed = true;
}

void MarketMenu::backFunction() {
    this->hide();
    game->gameMenu.display();
}

void MarketMenu::hide() {
    infoLabel.setVisible(false);
    infoLabel.setEnabled(false);

    descriptionLabel.setVisible(false);
    descriptionLabel.setEnabled(false);

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

    displayed = false;
}

MarketMenu::~MarketMenu() {

}
