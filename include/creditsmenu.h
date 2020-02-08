#ifndef INCLUDE_CREDITSMENU_H_
#define INCLUDE_CREDITSMENU_H_
#include <QLabel>
#include <QPushButton>
#include "menu.h"

class CreditsMenu : public Menu {
private:
    Q_OBJECT
private:
    QLabel creditsLabel,
           contributorsListLabel;
    QPushButton backButton;
private slots:
    void backFunction() override;
public:
    CreditsMenu(Game *game, QGridLayout *grid);
    ~CreditsMenu() override;
    void display() override;
    void hide() override;
};

#endif  // INCLUDE_CREDITSMENU_H_
