#ifndef INCLUDE_LOTTERYMENU_H_
#define INCLUDE_LOTTERYMENU_H_
#include <QPushButton>
#include "menu.h"

class LotteryMenu : public Menu {
private:
    Q_OBJECT
private:
    QPushButton backButton;
private slots:
    void backFunction() override;
public:
    LotteryMenu(Game *game, QGridLayout *grid);
    ~LotteryMenu();
    void display() override;
    void hide() override;
};

#endif  // INCLUDE_LOTTERYMENU_H_
