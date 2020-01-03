#include "statisticsmenu.h"
#include "game.h"

StatisticsMenu::StatisticsMenu(Game *game, QGridLayout *grid) :
        Menu(game, grid) {
    grid->addWidget(&statisticsLabel, 0, 1);
    statisticsLabel.setVisible(false);

    grid->addWidget(&statisticsText, 1, 0, 1, 3);
    statisticsText.setReadOnly(true);
    statisticsText.setVisible(false);
    statisticsText.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    statisticsText.setTextInteractionFlags(Qt::NoTextInteraction);
    statisticsText.setFrameStyle(QFrame::NoFrame);

    grid->addWidget(&itemsButton, 2, 0);
    itemsButton.setVisible(false);
    itemsButton.setEnabled(false);
    connect(&itemsButton, SIGNAL(released()), this, SLOT(itemsFunction()));

    grid->addWidget(&coinsButton, 2, 1);
    coinsButton.setVisible(false);
    coinsButton.setEnabled(false);
    connect(&coinsButton, SIGNAL(released()), this, SLOT(coinsFunction()));

    grid->addWidget(&backButton, 3, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void StatisticsMenu::updateStatistics() {
    qDebug() << "Statistics have been updated";
    QString statText;
    auto stats = game->users[game->activeUser].getStatistics(game);
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

void StatisticsMenu::display() {
    this->pre_display();

    timerUpdater = connect(&timer, SIGNAL(timeout()), this, SLOT(updateStatistics()));
    timer.start(Config::STATISTICS_UPDATE_PERIOD);
    updateStatistics();

    statisticsLabel.setText(game->str.statistics);
    statisticsLabel.setVisible(true);

    statisticsText.setVisible(true);

    itemsButton.setText(game->str.items);
    itemsButton.setVisible(true);
    itemsButton.setEnabled(true);

    coinsButton.setText(game->str.coins);
    coinsButton.setVisible(true);
    coinsButton.setEnabled(true);

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);

    displayed = true;
}

void StatisticsMenu::backFunction() {
    this->hide();
    game->gameMenu.display();
}

void StatisticsMenu::itemsFunction() {
    this->hide();
    game->itemStatisticsMenu.display();
}

void StatisticsMenu::coinsFunction() {
    this->hide();
    game->coinStatisticsMenu.display();
}

void StatisticsMenu::hide() {
    this->pre_hide();

    timer.stop();
    disconnect(timerUpdater);

    statisticsLabel.setVisible(false);

    statisticsText.setVisible(false);

    itemsButton.setVisible(false);
    itemsButton.setEnabled(false);

    coinsButton.setVisible(false);
    coinsButton.setEnabled(false);

    backButton.setVisible(false);
    backButton.setEnabled(false);

    displayed = false;
}

StatisticsMenu::~StatisticsMenu() {

}
