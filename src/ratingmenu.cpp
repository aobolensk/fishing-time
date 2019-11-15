#include <algorithm>
#include <QHeaderView>
#include "ratingmenu.h"
#include "game.h"

RatingMenu::RatingMenu(Game *game, QGridLayout *grid) :
        Menu(game, grid) {
    grid->addWidget(&ratingTable, 0, 0, 2, 3);
    ratingTable.setRowCount(0);
    ratingTable.setColumnCount(3);
    ratingTable.setSelectionMode(QAbstractItemView::NoSelection);
    ratingTable.setHorizontalHeaderItem(0, &usernameHeader);
    ratingTable.setHorizontalHeaderItem(1, &levelHeader);
    ratingTable.setHorizontalHeaderItem(2, &expHeader);
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
            game->users[i].getLevel(),
            game->users[i].getExperience(),
        };
    }
    std::sort(rows.begin(), rows.end(), [](const RatingRow &a, const RatingRow &b) {
        return a.exp > b.exp;
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
        cell->setText(QString::number(rows[i].level));
        cell->setFlags(cell->flags() & (~Qt::ItemIsEditable));
        cell = ratingTable.item(i, 2);
        if (!cell) {
            cell = new QTableWidgetItem;
            ratingTable.setItem(i, 2, cell);
        }
        cell->setText(QString::number(rows[i].exp));
        cell->setFlags(cell->flags() & (~Qt::ItemIsEditable));
    }
}

void RatingMenu::display() {
    this->pre_display();

    updateTable();

    usernameHeader.setText(game->str.username);
    levelHeader.setText(game->str.level);
    expHeader.setText(game->str.experience);

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
    this->pre_hide();

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
