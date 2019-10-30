#include "statisticsmenu.h"
#include "game.h"

StatisticsMenu::StatisticsMenu(Game *game, QGridLayout *grid) :
        game(game),
        grid(grid) {
    grid->addWidget(&statisticsText, 0, 0, 1, 3);
    statisticsText.setReadOnly(true);
    statisticsText.setVisible(false);
    statisticsText.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    statisticsText.setTextInteractionFlags(Qt::NoTextInteraction);
    statisticsText.setFrameStyle(QFrame::NoFrame);

    grid->addWidget(&itemsButton, 1, 0);
    itemsButton.setVisible(false);
    itemsButton.setEnabled(false);
    connect(&itemsButton, SIGNAL(released()), this, SLOT(itemsFunction()));

    grid->addWidget(&backButton, 2, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

bool StatisticsMenu::isDisplayed() const {
    return displayed;
}

void StatisticsMenu::updateStatistics() {
    qDebug() << "Statistics have been updated";
    QString statText;
    auto stats = game->users[game->activeUser].getStatistsics(game);
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
    timerUpdater = connect(&timer, SIGNAL(timeout()), this, SLOT(updateStatistics()));
    timer.start(Config::STATISTICS_UPDATE_PERIOD);
    updateStatistics();
    statisticsText.setVisible(true);

    itemsButton.setText(game->str.items);
    itemsButton.setVisible(true);
    itemsButton.setEnabled(true);

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

void StatisticsMenu::hide() {
    timer.stop();
    disconnect(timerUpdater);

    statisticsText.setVisible(false);

    itemsButton.setVisible(false);
    itemsButton.setEnabled(false);

    backButton.setVisible(false);
    backButton.setEnabled(false);

    displayed = false;
}

StatisticsMenu::~StatisticsMenu() {

}
