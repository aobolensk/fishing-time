#ifndef INCLUDE_STATISTICSMENU_H_
#define INCLUDE_STATISTICSMENU_H_
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QTimer>
#include "menu.h"

class StatisticsMenu : public Menu {
private:
    Q_OBJECT
private:
    QLabel statisticsLabel;
    QTextEdit statisticsText;
    QPushButton itemsButton,
                coinsButton,
                backButton;
    QTimer timer;
    QMetaObject::Connection timerUpdater;
private slots:
    void updateStatistics();
    void itemsFunction();
    void coinsFunction();
    void backFunction() override;
public:
    StatisticsMenu(Game *game, QGridLayout *grid);
    ~StatisticsMenu() override;
    void display() override;
    void hide() override;
};

#endif  // INCLUDE_STATISTICSMENU_H_
