#ifndef INCLUDE_RATINGMENU_H_
#define INCLUDE_RATINGMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QTableWidget>
#include "menu.h"

class RatingMenu : public Menu {
private:
    Q_OBJECT
private:
    Game *game;
    QTableWidget ratingTable;
    QTableWidgetItem usernameHeader,
                     coinsHeader;
    QPushButton backButton;
    QGridLayout *grid;
    struct RatingRow {
        QString username;
        qint64 coins;
    };
    QVector <RatingRow> rows;
private:
    void updateTable();
private slots:
    void backFunction();
public:
    RatingMenu(Game *game, QGridLayout *grid);
    ~RatingMenu();
    void display() override;
    void hide() override;
};

#endif  // INCLUDE_RATINGMENU_H_
