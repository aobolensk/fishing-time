#ifndef INCLUDE_CONTROLSMENU_H_
#define INCLUDE_CONTROLSMENU_H_
#include <QPushButton>
#include "menu.h"

class ControlsMenu : public Menu {
private:
    Q_OBJECT
private:
    QPushButton backButton;
private slots:
    void backFunction() override;
public:
    ControlsMenu(Game *game, QGridLayout *grid);
    ~ControlsMenu();
    void display() override;
    void hide() override;
};

#endif  // INCLUDE_CONTROLSMENU_H_
