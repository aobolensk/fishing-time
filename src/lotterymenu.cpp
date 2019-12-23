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

    grid->addWidget(&backButton, 10, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void LotteryMenu::display() {
    this->pre_display();

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
    QString currentTicket = ticketSelector.currentText().split(" ").first();
    ticketLabel.setText(currentTicket);

    ticketGrid = new QGridLayout(nullptr);
    grid->addLayout(ticketGrid, 3, 0, 1, 3);
    if (currentTicket == "ticket.basic") {
        for (int i = 0; i < Config::LOTTERY_BUTTONS_COUNT; ++i) {
            ticketGrid->addWidget(&numberButton[i], i / 10, i % 10);
            numberButton[i].setText(QString::number(i + 1));
            numberButton[i].setVisible(true);
            numberButton[i].setEnabled(true);
        }
    }
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

    for (int i = 0; i < Config::LOTTERY_BUTTONS_COUNT; ++i) {
        numberButton[i].setText(QString::number(i + 1));
        numberButton[i].setVisible(false);
        numberButton[i].setEnabled(false);
    }
    delete ticketGrid;
    ticketGrid = nullptr;

    backButton.setVisible(false);
    backButton.setEnabled(false);

    displayed = false;
}

LotteryMenu::~LotteryMenu() {

}
