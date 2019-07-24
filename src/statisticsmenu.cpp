#include "statisticsmenu.h"
#include "game.h"

StatisticsMenu::StatisticsMenu(Game *game, QGridLayout *grid) :
        game(game),
        grid(grid) {
    grid->addWidget(&statisticsText, 0, 0, 1, 3);
    statisticsText.setTextFormat(Qt::RichText);
    statisticsText.setVisible(false);

    grid->addWidget(&backButton, 1, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void StatisticsMenu::display() {
    statisticsText.setText(
        QString("<table border=\"1\" width=\"100%\">"
                    "<tr>"
                        "<td>%1</td>"
                        "<td>%2</td>"
                    "</tr>"
                "</table>")
        .arg(
            game->str.clicksCount,
            QString::number(game->users[game->activeUser].getClicks())
        ));
    statisticsText.setVisible(true);

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);
}

void StatisticsMenu::backFunction() {
    this->hide();
    game->gameMenu.display();
}

void StatisticsMenu::hide() {
    statisticsText.setVisible(false);

    backButton.setVisible(false);
    backButton.setEnabled(false);
}

StatisticsMenu::~StatisticsMenu() {

}
