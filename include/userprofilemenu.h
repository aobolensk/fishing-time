#ifndef INCLUDE_USERPROFILEMENU_H_
#define INCLUDE_USERPROFILEMENU_H_
#include <QLabel>
#include <QPushButton>
#include "menu.h"

class UserProfileMenu : public Menu {
private:
    Q_OBJECT
private:
    QPushButton backButton;
private slots:
    void backFunction() override;
public:
    UserProfileMenu(Game *game, QGridLayout *grid);
    ~UserProfileMenu();
    void display() override;
    void hide() override;
};

#endif  // INCLUDE_USERPROFILEMENU_H_
