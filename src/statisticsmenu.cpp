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
    statText += "<table border=\"1\" width=\"100%\" table-layout=\"fixed\">";
    statText += QString(
        "<tr>"
            "<td colspan=\"3\">%1</td>"
        "</tr>"
    ).arg(
        game->str.itemStatistics
    );
    statText += QString(
        "<tr>"
            "<td align=\"center\">%1</td>"
            "<td align=\"center\">%2</td>"
            "<td align=\"center\">%3</td>"
            "<td align=\"center\">%4</td>"
        "</tr>"
    ).arg(
        game->str.item,
        game->str.stats["got"],
        game->str.stats["sold"],
        game->str.stats["bought"]
    );
    auto it2 = game->str.itemNames.cbegin();
    Q_ASSERT(game->str.itemNames.size() > 1);
    const auto &itemStats = game->users[game->activeUser].inventory.getItemStats();
    while (it2 != game->str.itemNames.cend()) {
        if (it2.key() != "item.undefined") {
            auto item = itemStats.find(it2.key());
            if (item == itemStats.end()) {
                ++it2;
                continue;
            }
            int gotValue = 0;
            if (item.value().find("got") != item.value().end()) {
                gotValue = item.value()["got"];
            }
            int soldValue = 0;
            if (item.value().find("sold") != item.value().end()) {
                soldValue = item.value()["sold"];
            }
            int boughtValue = 0;
            if (item.value().find("bought") != item.value().end()) {
                boughtValue = item.value()["bought"];
            }
            statText += QString(
                "<tr>"
                    "<td align=\"center\">%1</td>"
                    "<td align=\"center\">%2</td>"
                    "<td align=\"center\">%3</td>"
                    "<td align=\"center\">%4</td>"
                "</tr>"
            ).arg(
                *it2.value(),
                QString::number(gotValue),
                QString::number(soldValue),
                QString::number(boughtValue)
            );
        }
        ++it2;
    }
    statText += "</table>";
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
