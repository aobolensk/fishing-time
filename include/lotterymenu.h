#ifndef INCLUDE_LOTTERYMENU_H_
#define INCLUDE_LOTTERYMENU_H_
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QSet>
#include "menu.h"
#include "config.h"

class LotteryMenu : public Menu {
private:
    Q_OBJECT
private:
    QString currentTicket;
    QLabel ticketLabel,
           comboLabel;
    QComboBox ticketSelector;
    QGridLayout *ticketGrid;
    QSet <int> combo;
    QPushButton selectTicketButton,
                numberButton[Config::LOTTERY_BUTTONS_COUNT],
                submitButton,
                backButton;
private slots:
    void selectTicketFunction();
    void submitFunction();
    void backFunction() override;
public:
    LotteryMenu(Game *game, QGridLayout *grid);
    ~LotteryMenu();
    void display() override;
    void hide() override;
};

#endif  // INCLUDE_LOTTERYMENU_H_
