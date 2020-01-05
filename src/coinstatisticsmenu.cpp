#include "game.h"
#include "coinstatisticsmenu.h"

CoinStatisticsMenu::CoinStatisticsMenu(Game *game, QGridLayout *grid) :
        Menu(game, grid) {
    grid->addWidget(&statisticsLabel, 0, 1);
    statisticsLabel.setVisible(false);
    statisticsLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

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

void CoinStatisticsMenu::updateStatistics() {
    QString statText;
    auto stats = game->users[game->activeUser].getCoinStatistics(game);
    auto it = stats.cbegin();
    statText += "<table border=\"1\" width=\"100%\">";
    while (it != stats.cend()) {
        statText += QString(
            "<tr>"
                "<td width=\"50%\">%1</td>"
                "<td width=\"50%\">%2</td>"
            "</tr>"
        ).arg(
            it->first,
            it->second
        );
        ++it;
    }
    statText += "</table>";
    statisticsText.setText(statText);
}

void CoinStatisticsMenu::display() {
    this->pre_display();

    updateStatistics();
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
