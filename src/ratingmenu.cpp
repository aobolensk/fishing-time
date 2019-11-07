#include <algorithm>
#include <QHeaderView>
#include "ratingmenu.h"
#include "game.h"

RatingMenu::RatingMenu(Game *game, QGridLayout *grid) :
        game(game),
        grid(grid) {
    grid->addWidget(&ratingTable, 0, 0, 2, 3);
    ratingTable.setRowCount(0);
    ratingTable.setColumnCount(2);
    ratingTable.setSelectionMode(QAbstractItemView::NoSelection);
    ratingTable.setHorizontalHeaderItem(0, &usernameHeader);
    ratingTable.setHorizontalHeaderItem(1, &coinsHeader);
    ratingTable.setVisible(false);
    ratingTable.setEnabled(false);

    grid->addWidget(&backButton, 2, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void RatingMenu::updateTable() {
    ratingTable.setRowCount(game->users.size());
    rows.resize(game->users.size());
    for (int i = 0; i < game->users.size(); ++i) {
        rows[i] = {
            game->users[i].getUsername(),
            game->users[i].getCoins()
        };
    }
    std::sort(rows.begin(), rows.end(), [](const RatingRow &a, const RatingRow &b) {
        return a.coins > b.coins;
    });
    for (int i = 0; i < game->users.size(); ++i) {
        QTableWidgetItem *cell = ratingTable.item(i, 0);
        if (!cell) {
            cell = new QTableWidgetItem;
            ratingTable.setItem(i, 0, cell);
        }
        cell->setText(rows[i].username);
        cell->setFlags(cell->flags() & (~Qt::ItemIsEditable));
        cell = ratingTable.item(i, 1);
        if (!cell) {
            cell = new QTableWidgetItem;
            ratingTable.setItem(i, 1, cell);
        }
        cell->setText(QString::number(rows[i].coins));
        cell->setFlags(cell->flags() & (~Qt::ItemIsEditable));
    }
}

void RatingMenu::display() {
    game->installEventFilter(this);

    updateTable();

    usernameHeader.setText(game->str.username);
    coinsHeader.setText(game->str.coins);

    ratingTable.horizontalHeader()->setFont(game->font());
    ratingTable.setVisible(true);
    ratingTable.setEnabled(true);

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);

    displayed = true;
}

void RatingMenu::backFunction() {
    this->hide();
    game->mainMenu.display();
}

void RatingMenu::hide() {
    game->removeEventFilter(this);

    ratingTable.setVisible(false);
    ratingTable.setEnabled(false);

    backButton.setVisible(false);
    backButton.setEnabled(false);

    displayed = false;
}

RatingMenu::~RatingMenu() {
    for (int i = 0; ; ++i) {
        int cnt = 0;
        for (int j = 0; j < 2; ++j) {
            if (ratingTable.item(i, j)) {
                ++cnt;
                delete ratingTable.item(i, j);
            }
        }
        if (!cnt) {
            break;
        }
    }
}
