#ifndef INCLUDE_LOTTERYMENU_H_
#define INCLUDE_LOTTERYMENU_H_
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include "menu.h"
#include "config.h"

class LotteryMenu : public Menu {
private:
    Q_OBJECT
private:
    QLabel ticketLabel;
    QComboBox ticketSelector;
    QGridLayout *ticketGrid;
    QPushButton selectTicketButton,
                numberButton[Config::LOTTERY_BUTTONS_COUNT],
                backButton;
private slots:
    void selectTicketFunction();
    void backFunction() override;
public:
    LotteryMenu(Game *game, QGridLayout *grid);
    ~LotteryMenu();
    void display() override;
    void hide() override;
};

#endif  // INCLUDE_LOTTERYMENU_H_
