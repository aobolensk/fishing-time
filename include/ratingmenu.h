#ifndef INCLUDE_RATINGMENU_H_
#define INCLUDE_RATINGMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>

class Game;

class RatingMenu : public QObject {
private:
    Q_OBJECT
private:
    Game *game;
    QPushButton backButton;
    QGridLayout *grid;
private slots:
    void backFunction();
public:
    RatingMenu(Game *game, QGridLayout *grid);
    ~RatingMenu();
    void display();
    void hide();
};

#endif  // INCLUDE_RATINGMENU_H_
