#ifndef INCLUDE_MENU_H_
#define INCLUDE_MENU_H_
#include <QGridLayout>
#include <QWidget>
#include "menu.h"

class Game;

class Menu : public QWidget {
protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
protected slots:
    virtual void backFunction();
protected:
    Game *game;
    QGridLayout *grid;
    bool displayed = false;
    bool floating = false;
    virtual void pre_display() final;
    virtual void pre_hide() final;
public:
    Menu(Game *game, QGridLayout *grid, bool floating = false);
    ~Menu();
    virtual void display() = 0;
    virtual void hide() = 0;
    bool isDisplayed() const;
};

#endif  // INCLUDE_MENU_H_
