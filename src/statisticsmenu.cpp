#include "statisticsmenu.h"
#include "game.h"

StatisticsMenu::StatisticsMenu(Game *game, QGridLayout *grid) :
        game(game),
        grid(grid) {
    grid->addWidget(&statisticsText, 0, 0, 1, 3);
    statisticsText.setReadOnly(true);
    statisticsText.setVisible(false);
    statisticsText.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    grid->addWidget(&backButton, 1, 1);
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
    while (it != stats.cend()) {
        statText += QString(
            "<table border=\"1\" width=\"100%\">"
                "<tr>"
                    "<td width=\"50%\">%1</td>"
                    "<td width=\"50%\">%2</td>"
                "</tr>"
            "</table>"
        ).arg(
            it->first,
            it->second
        );
        ++it;
    }
    statText += QString(
        "<table border=\"1\" width=\"100%\">"
            "<tr>"
                "<td width=\"100%\">Items statistics:</td>"
            "</tr>"
        "</table>"
    );
    statText += QString(
        "<table border=\"1\" width=\"100%\">"
            "<tr>"
                "<td width=\"50%\" align=\"center\">Item name</td>"
                "<td width=\"50%\" align=\"center\">Got</td>"
            "</tr>"
        "</table>"
    );
    auto it2 = game->str.itemNames.cbegin();
    Q_ASSERT(game->str.itemNames.size() > 1);
    const auto &itemStats = game->users[game->activeUser].inventory.getItemStats();
    while (it2 != game->str.itemNames.cend()) {
        if (it2.key() != "item.undefined") {
            auto item = itemStats.find(it2.key());
            int gotValue = 0;
            if (item != itemStats.end()) {
                gotValue = item.value().got;
            }
            statText += QString(
                "<table border=\"1\" width=\"100%\">"
                    "<tr>"
                        "<td width=\"50%\" align=\"center\">%1</td>"
                        "<td width=\"50%\" align=\"center\">%2</td>"
                    "</tr>"
                "</table>"
            ).arg(
                *it2.value(),
                QString::number(gotValue)
            );
        }
        ++it2;
    }
    statisticsText.setText(statText);
}

void StatisticsMenu::display() {
    timerUpdater = connect(&timer, SIGNAL(timeout()), this, SLOT(updateStatistics()));
    timer.start(1000);
    updateStatistics();
    statisticsText.setVisible(true);

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);

    displayed = true;
}

void StatisticsMenu::backFunction() {
    timer.stop();
    disconnect(timerUpdater);

    this->hide();
    game->gameMenu.display();
}

void StatisticsMenu::hide() {
    statisticsText.setVisible(false);

    backButton.setVisible(false);
    backButton.setEnabled(false);

    displayed = false;
}

StatisticsMenu::~StatisticsMenu() {

}
