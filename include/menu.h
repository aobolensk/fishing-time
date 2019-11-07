#ifndef INCLUDE_MENU_H_
#define INCLUDE_MENU_H_
#include <QWidget>
#include "menu.h"

class Game;

class Menu : public QWidget {
protected:
    bool eventFilter(QObject *obj, QEvent *event);
protected slots:
    virtual void backFunction();
protected:
    bool displayed = false;
    virtual void pre_display() final;
    virtual void pre_hide() final;
public:
    virtual void display() = 0;
    virtual void hide() = 0;
    bool isDisplayed() const;
};

#endif  // INCLUDE_MENU_H_
