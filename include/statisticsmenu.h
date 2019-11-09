#ifndef INCLUDE_STATISTICSMENU_H_
#define INCLUDE_STATISTICSMENU_H_
#include <QPushButton>
#include <QTextEdit>
#include <QTimer>
#include "menu.h"

class StatisticsMenu : public Menu {
private:
    Q_OBJECT
private:
    QTextEdit statisticsText;
    QPushButton itemsButton,
                backButton;
    QTimer timer;
    QMetaObject::Connection timerUpdater;
private slots:
    void updateStatistics();
    void itemsFunction();
    void backFunction() override;
public:
    StatisticsMenu(Game *game, QGridLayout *grid);
    ~StatisticsMenu();
    void display() override;
    void hide() override;
};

#endif  // INCLUDE_STATISTICSMENU_H_
