#ifndef INCLUDE_COINSTATISTICSMENU_H_
#define INCLUDE_COINSTATISTICSMENU_H_
#include <QPushButton>
#include <QTextEdit>
#include "menu.h"

class CoinStatisticsMenu : public Menu {
private:
    Q_OBJECT
private:
    QLabel statisticsLabel;
    QTextEdit statisticsText;
    QPushButton backButton;
private slots:
    void backFunction() override;
public:
    CoinStatisticsMenu(Game *game, QGridLayout *grid);
    ~CoinStatisticsMenu();
    void display() override;
    void hide() override;
};

#endif  // INCLUDE_COINSTATISTICSMENU_H_
