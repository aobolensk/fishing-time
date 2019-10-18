#ifndef INCLUDE_MENU_H_
#define INCLUDE_MENU_H_
#include <QWidget>
#include "menu.h"

class Game;

class Menu : public QWidget {
public:
    virtual void display() = 0;
    virtual void hide() = 0;
};

#endif  // INCLUDE_MENU_H_
