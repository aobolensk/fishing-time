#include <QVector>
#include "lotterymenu.h"
#include "game.h"

LotteryMenu::LotteryMenu(Game *game, QGridLayout *grid) :
        Menu(game, grid) {
    grid->addWidget(&ticketSelector, 1, 1);
    ticketSelector.setVisible(false);
    ticketSelector.setEnabled(false);

    grid->addWidget(&selectTicketButton, 1, 2);
    selectTicketButton.setVisible(false);
    selectTicketButton.setEnabled(false);
    connect(&selectTicketButton, SIGNAL(released()), this, SLOT(selectTicketFunction()));

    grid->addWidget(&ticketLabel, 2, 1);
    ticketLabel.setVisible(false);

    // 3rd row is reserved for ticket grid

    grid->addWidget(&comboLabel, 4, 0, 1, 3);
    comboLabel.setVisible(false);
    comboLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    grid->addWidget(&submitButton, 5, 1);
    submitButton.setVisible(false);
    submitButton.setEnabled(false);
    connect(&submitButton, SIGNAL(released()), this, SLOT(submitFunction()));

    grid->addWidget(&backButton, 10, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void LotteryMenu::display() {
    this->pre_display();

    currentTicket = "";
    comboLabel.setText("");
    ticketLabel.setText("");

    QMap <QString, int>::const_iterator item = game->users[game->activeUser].inventory.get().begin();
    for (; item != game->users[game->activeUser].inventory.get().end(); ++item) {
        if (item.key().startsWith("ticket.")) {
            ticketSelector.addItem(item.key() + " (" + QString::number(item.value()) + ")");
        }
    }
    ticketSelector.setVisible(true);
    ticketSelector.setEnabled(true);

    selectTicketButton.setText(game->str.select);
    selectTicketButton.setVisible(true);
    selectTicketButton.setEnabled(true);

    ticketLabel.setVisible(true);

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);

    displayed = true;
}

void LotteryMenu::selectTicketFunction() {
    currentTicket = ticketSelector.currentText().split(" ").first();
    ticketLabel.setText(currentTicket);
    combo.clear();

    ticketSelector.clear();
    ticketSelector.setVisible(false);
    ticketSelector.setEnabled(false);

    selectTicketButton.setVisible(false);
    selectTicketButton.setEnabled(false);

    ticketGrid = new QGridLayout(nullptr);
    grid->addLayout(ticketGrid, 3, 0, 1, 3);

    comboLabel.setVisible(true);

    if (currentTicket == "ticket.basic") {
        for (int i = 0; i < Config::LOTTERY_BUTTONS_COUNT; ++i) {
            ticketGrid->addWidget(&numberButton[i], i / 10, i % 10);
            numberButton[i].setText(QString::number(i + 1));
            numberButton[i].setVisible(true);
            numberButton[i].setEnabled(true);
            connect(&numberButton[i], &QPushButton::clicked, [this, i]() {
                if (combo.find(i + 1) == combo.end()) {
                    if (combo.size() < Config::LOTTERY_NEED_BUTTONS_COUNT) {
                        combo.insert(i + 1);
                    }
                } else {
                    combo.erase(combo.find(i + 1));
                }
                QList <int> sortedCombo = combo.toList();
                std::sort(sortedCombo.begin(), sortedCombo.end());
                QString comboText = game->str.combination + ": {";
                bool first = true;
                for (int x : sortedCombo) {
                    if (!first) {
                        comboText += ", " + QString::number(x);
                    } else {
                        comboText += QString::number(x);
                        first = false;
                    }
                }
                comboText += "}";
                comboLabel.setText(comboText);
            });
        }
    }

    submitButton.setText(game->str.submit);
    submitButton.setVisible(true);
    submitButton.setEnabled(true);
}

void LotteryMenu::submitFunction() {
    if (combo.size() != 7) {
        return;
    }
    QVector <int> answer(Config::LOTTERY_BUTTONS_COUNT);
    std::iota(answer.begin(), answer.end(), 1);
    std::mt19937 rng(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::shuffle(answer.begin(), answer.end(), rng);
    answer.resize(Config::LOTTERY_NEED_BUTTONS_COUNT);
    std::sort(answer.begin(), answer.end());
    QString expectedText = game->str.answer + ": {";
    bool first = true;
    for (int x : answer) {
        if (!first) {
            expectedText += ", " + QString::number(x);
        } else {
            expectedText += QString::number(x);
            first = false;
        }
    }
    expectedText += "}";
    comboLabel.setText(comboLabel.text() + "\n" + expectedText);
    int matchings = 0;
    for (int x : combo) {
        if (std::find(answer.begin(), answer.end(), x) != answer.end()) {
            ++matchings;
        }
    }
    comboLabel.setText(comboLabel.text() + "\n" +
                       game->str.matchingsFound.arg(QString::number(matchings)) + "\n" +
                       game->str.coinsEarned.arg(QString::number(matchings * 100)) + "\n");
    game->users[game->activeUser].changeCoins(matchings * 100);
    game->users[game->activeUser].inventory.changeItem(currentTicket, -1);

    submitButton.setVisible(false);
    submitButton.setEnabled(false);
}

void LotteryMenu::backFunction() {
    this->hide();
    game->marketMenu.display();
}

void LotteryMenu::hide() {
    this->pre_hide();

    ticketSelector.clear();
    ticketSelector.setVisible(false);
    ticketSelector.setEnabled(false);

    selectTicketButton.setVisible(false);
    selectTicketButton.setEnabled(false);

    ticketLabel.setVisible(false);

    comboLabel.setVisible(false);

    for (int i = 0; i < Config::LOTTERY_BUTTONS_COUNT; ++i) {
        numberButton[i].setText(QString::number(i + 1));
        numberButton[i].setVisible(false);
        numberButton[i].setEnabled(false);
        numberButton[i].disconnect();
    }
    delete ticketGrid;
    ticketGrid = nullptr;

    submitButton.setVisible(false);
    submitButton.setEnabled(false);

    backButton.setVisible(false);
    backButton.setEnabled(false);

    displayed = false;
}

LotteryMenu::~LotteryMenu() {

}
