#ifndef INCLUDE_CREDITSMENU_H_
#define INCLUDE_CREDITSMENU_H_
#include <QPushButton>
#include "menu.h"

class CreditsMenu : public Menu {
private:
    Q_OBJECT
private:
    QPushButton backButton;
private slots:
    void backFunction() override;
public:
    CreditsMenu(Game *game, QGridLayout *grid);
    ~CreditsMenu();
    void display() override;
    void hide() override;
};

#endif  // INCLUDE_CREDITSMENU_H_
