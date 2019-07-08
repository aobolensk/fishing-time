#include <random>
#include <QDateTime>
#include "gamemenu.h"
#include "mainwindow.h"

MarketMenu::MarketMenu(MainWindow *w, QGridLayout *g) :
        window(w),
        grid(g) {
    for (int i = 0; i < SELLERS_COUNT; ++i) {
        grid->addWidget(&dialogButton[i], 2, i);
        dialogButton[i].setVisible(false);
        grid->addWidget(&dialogLabel[i], 1, i);
        dialogLabel[i].setVisible(false);
    }

    grid->addWidget(&backButton, 3, 2);
    backButton.setVisible(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void MarketMenu::display() {
    std::mt19937 randGen(QDateTime::currentDateTime().daysTo(QDateTime(QDate(2019, 1, 1), QTime(0, 0))));
    std::uniform_int_distribution<> gen(0, window->str.itemIds.size() - 1); 
    for (int i = 0; i < 3; ++i) {
        dialogButton[i].setText(window->str.dialog);
        dialogButton[i].setVisible(true);
        dialogLabel[i].setText("Seller " + QString::number(i) + "\nbuys " +
                window->str.getItemName(window->str.itemIds[gen(randGen)]) + "\nfor " + QString::number(randGen() % 100) + " coins each");
        dialogLabel[i].setVisible(true);
    }
    backButton.setText(window->str.back);
    backButton.setVisible(true);
}

void MarketMenu::backFunction() {
    this->hide();
    window->gameMenu.display();
}

void MarketMenu::hide() {
    for (int i = 0; i < SELLERS_COUNT; ++i) {
        dialogButton[i].setVisible(false);
        dialogLabel[i].setVisible(false);
    }
    backButton.setVisible(false);
}

MarketMenu::~MarketMenu() {

}
