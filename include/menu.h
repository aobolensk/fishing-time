#ifndef INCLUDE_MENU_H_
#define INCLUDE_MENU_H_
#include <QWidget>
#include <QGridLayout>
#include "menu.h"

class Game;

class Menu : public QWidget {
protected:
    bool eventFilter(QObject *obj, QEvent *event);
protected slots:
    virtual void backFunction();
protected:
    Game *game;
    QGridLayout *grid;
    bool displayed = false;
    virtual void pre_display() final;
    virtual void pre_hide() final;
public:
    Menu(Game *game, QGridLayout *grid);
    ~Menu();
    virtual void display() = 0;
    virtual void hide() = 0;
    bool isDisplayed() const;
};

#endif  // INCLUDE_MENU_H_
