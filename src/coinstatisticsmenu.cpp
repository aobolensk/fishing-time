#include "game.h"
#include "coinstatisticsmenu.h"

CoinStatisticsMenu::CoinStatisticsMenu(Game *game, QGridLayout *grid) :
        Menu(game, grid) {
    grid->addWidget(&statisticsLabel, 0, 1);
    statisticsLabel.setVisible(false);

    grid->addWidget(&statisticsText, 1, 0, 1, 3);
    statisticsText.setReadOnly(true);
    statisticsText.setVisible(false);
    statisticsText.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    statisticsText.setTextInteractionFlags(Qt::NoTextInteraction);
    statisticsText.setFrameStyle(QFrame::NoFrame);

    grid->addWidget(&backButton, 2, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void CoinStatisticsMenu::display() {
    this->pre_display();

    statisticsLabel.setText(game->str.coinStatistics);
    statisticsLabel.setVisible(true);

    statisticsText.setVisible(true);

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);

    displayed = true;
}

void CoinStatisticsMenu::backFunction() {
    this->hide();
    game->statisticsMenu.display();
}

void CoinStatisticsMenu::hide() {
    this->pre_hide();

    statisticsLabel.setVisible(false);

    statisticsText.setVisible(false);

    backButton.setVisible(false);
    backButton.setEnabled(false);

    displayed = false;
}

CoinStatisticsMenu::~CoinStatisticsMenu() {

}
