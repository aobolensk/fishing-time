#ifndef INCLUDE_STATISTICSMENU_H_
#define INCLUDE_STATISTICSMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QTimer>
#include "menu.h"

class StatisticsMenu : public Menu {
private:
    Q_OBJECT
private:
    bool displayed = false;
    Game *game;
    QLabel statisticsText;
    QPushButton backButton;
    QGridLayout *grid;
    QTimer timer;
    QMetaObject::Connection timerUpdater;
private slots:
    void updateStatistics();
    void backFunction();
public:
    StatisticsMenu(Game *game, QGridLayout *grid);
    ~StatisticsMenu();
    void display() override;
    void hide() override;
    bool isDisplayed() const;
};

#endif  // INCLUDE_STATISTICSMENU_H_
