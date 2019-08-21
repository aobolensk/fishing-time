#ifndef INCLUDE_RATINGMENU_H_
#define INCLUDE_RATINGMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QTableWidget>

class Game;

class RatingMenu : public QObject {
private:
    Q_OBJECT
private:
    Game *game;
    QTableWidget ratingTable;
    QTableWidgetItem usernameHeader,
                     coinsHeader;
    QPushButton backButton;
    QGridLayout *grid;
private:
    void updateTable();
private slots:
    void backFunction();
public:
    RatingMenu(Game *game, QGridLayout *grid);
    ~RatingMenu();
    void display();
    void hide();
};

#endif  // INCLUDE_RATINGMENU_H_
