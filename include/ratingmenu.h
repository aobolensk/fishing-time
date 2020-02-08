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
                     levelHeader,
                     expHeader;
    QPushButton backButton;
    struct RatingRow {
        QString username;
        int level;
        qint64 exp;
    };
    QVector <RatingRow> rows;
private:
    void updateTable();
private slots:
    void backFunction() override;
public:
    RatingMenu(Game *game, QGridLayout *grid);
    ~RatingMenu() override;
    void display() override;
    void hide() override;
};

#endif  // INCLUDE_RATINGMENU_H_
