#include <QDateTime>
#include <QMessageBox>
#include "gamemenu.h"
#include "game.h"

MarketMenu::MarketMenu(Game *game, QGridLayout *grid) :
        Menu(game, grid) {
    grid->addWidget(&descriptionLabel, 0, 0, 1, 2);
    descriptionLabel.setVisible(false);
    descriptionLabel.setEnabled(false);
    descriptionLabel.setWordWrap(true);

    grid->addWidget(&infoLabel, 0, 2);
    infoLabel.setVisible(false);
    infoLabel.setEnabled(false);
    infoLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    for (int i = 0; i < Config::SELLERS_COUNT; ++i) {
        dialogLabel[i].setWordWrap(true);
        dialogLabel[i].setVisible(false);
        dialogLabel[i].setEnabled(false);
        dialogLabel[i].setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        grid->addWidget(&dialogLabel[i], 1, i);
        quantityText[i].setText("0");
        quantityText[i].setVisible(false);
        quantityText[i].setEnabled(false);
        grid->addWidget(&quantityText[i], 2, i);
        dialogButton[i].setVisible(false);
        dialogButton[i].setEnabled(false);
        grid->addWidget(&dialogButton[i], 3, i);
        connect(&dialogButton[i], &QPushButton::clicked, [this, i](){processDialog(i);});
    }

    grid->addWidget(&lotteryButton, 4, 1);
    lotteryButton.setVisible(false);
    lotteryButton.setEnabled(false);
    connect(&lotteryButton, SIGNAL(released()), this, SLOT(lotteryFunction()));

    grid->addWidget(&backButton, 4, 2);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

static int hash(int x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}

void MarketMenu::updateDeals() {
    int currentSeed = QDateTime::currentDateTime().daysTo(QDateTime(QDate(2019, 1, 1), QTime(0, 0)));
    if (seed == currentSeed) {
        qDebug() << "Seed is not changed";
        return;
    }
    seed = currentSeed;
    std::mt19937 randGen(seed + hash(game->activeLocation + 1));
    qDebug() << "Random seed:" << seed + hash(game->activeLocation + 1);
    std::uniform_int_distribution<> gen(0, game->str.fishIds.size() - 2);
    for (int i = 0; i < Config::SELLERS_COUNT; ++i) {
        goodId[i] = game->str.fishIds[gen(randGen)];
        goodPrice[i] = randGen() % 100;
    }
}

QString MarketMenu::getDealInfo(int seller) {
    if (game->getCurrentMenu() != this) {
        this->updateDeals();
    }
    return game->str.sellerText.arg(
        QString::number(seller),
        game->str.getItemName(goodId[seller]),
        QString::number(goodPrice[seller]),
        QString::number(game->users[game->activeUser].inventory.getItem(goodId[seller]))
    );
}

void MarketMenu::setQuantity(int index, int quantity) {
    this->quantityText[index].setText(QString::number(quantity));
}

void MarketMenu::updateInfo() {
    infoLabel.setText(game->str.mainLabelText.arg(
        game->users[game->activeUser].getUsername(),
        QString::number(game->users[game->activeUser].getLevel()),
        QString::number(game->users[game->activeUser].getRemainingForNextLevel()),
        QString::number(game->users[game->activeUser].getNeededForNextLevel()),
        QString::number(game->users[game->activeUser].getCoins()),
        QString::number(game->users[game->activeUser].getClicks())
    ));

    for (int i = 0; i < Config::SELLERS_COUNT; ++i) {
        dialogLabel[i].setText(this->getDealInfo(i));
    }
    game->gameMenu.getPopUpInventoryTable().updateInventoryTables();
}

void MarketMenu::processDialog(int seller) {
    game->logger.info("Processing dialog for seller" + QString::number(seller));
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
    game->users[game->activeUser].inventory.updateStats(goodId[seller], "stats.sold", quantity);
    game->users[game->activeUser].changeExperience(quantity);
    game->logger.info("Sold " + QString::number(quantity) + " of " + goodId[seller] + " to seller " + QString::number(seller));
    game->logger.info("Earned " +  QString::number(goodPrice[seller] * quantity) + " coins");
    updateInfo();
}

void MarketMenu::display() {
    this->pre_display();

    if (!game->locations[game->activeLocation].getHasMarket()) {
        backFunction();
        return;
    }

    timerUpdater = connect(&timer, SIGNAL(timeout()), this, SLOT(updateDeals()));
    timer.start(Config::MARKET_UPDATE_PERIOD);

    updateDeals();
    updateInfo();

    descriptionLabel.setText(game->str.marketDescription);
    descriptionLabel.setVisible(true);
    descriptionLabel.setEnabled(true);

    infoLabel.setVisible(true);
    infoLabel.setEnabled(true);

    for (int i = 0; i < Config::SELLERS_COUNT; ++i) {
        dialogButton[i].setText(game->str.dialog);
        dialogButton[i].setVisible(true);
        dialogButton[i].setEnabled(true);

        dialogLabel[i].setVisible(true);
        dialogLabel[i].setEnabled(true);

        quantityText[i].setVisible(true);
        quantityText[i].setEnabled(true);
    }

    lotteryButton.setText(game->str.lottery);
    lotteryButton.setVisible(true);
    lotteryButton.setEnabled(true);

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);

    displayed = true;
}

void MarketMenu::lotteryFunction() {
    this->hide();
    game->lotteryMenu.display();
}

void MarketMenu::backFunction() {
    this->hide();
    game->gameMenu.display();
}

void MarketMenu::hide() {
    this->pre_hide();

    timer.stop();
    disconnect(timerUpdater);
    seed = -1;

    infoLabel.setVisible(false);
    infoLabel.setEnabled(false);

    descriptionLabel.setVisible(false);
    descriptionLabel.setEnabled(false);

    for (int i = 0; i < Config::SELLERS_COUNT; ++i) {
        dialogButton[i].setVisible(false);
        dialogButton[i].setEnabled(false);

        dialogLabel[i].setVisible(false);
        dialogLabel[i].setEnabled(false);

        quantityText[i].setVisible(false);
        quantityText[i].setEnabled(false);
    }

    lotteryButton.setVisible(false);
    lotteryButton.setEnabled(false);

    backButton.setVisible(false);
    backButton.setEnabled(false);

    displayed = false;
}

MarketMenu::~MarketMenu() {

}
