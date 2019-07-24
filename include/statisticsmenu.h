#ifndef INCLUDE_STATISTICSMENU_H_
#define INCLUDE_STATISTICSMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>

class Game;

class StatisticsMenu : public QObject {
private:
    Q_OBJECT
private:
    Game *game;
    QLabel statisticsText;
    QPushButton backButton;
    QGridLayout *grid;
private slots:
    void backFunction();
public:
    StatisticsMenu(Game *game, QGridLayout *grid);
    ~StatisticsMenu();
    void display();
    void hide();
};

#endif  // INCLUDE_STATISTICSMENU_H_
