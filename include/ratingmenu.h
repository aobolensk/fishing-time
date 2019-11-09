#ifndef INCLUDE_RATINGMENU_H_
#define INCLUDE_RATINGMENU_H_
#include <QPushButton>
#include <QTableWidget>
#include "menu.h"

class RatingMenu : public Menu {
private:
    Q_OBJECT
private:
    QTableWidget ratingTable;
    QTableWidgetItem usernameHeader,
                     coinsHeader;
    QPushButton backButton;
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
