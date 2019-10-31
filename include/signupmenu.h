#ifndef INCLUDE_SIGNUPMENU_H_
#define INCLUDE_SIGNUPMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include "menu.h"

class SignupMenu : public Menu {
private:
    Q_OBJECT
private:
    Game *game;
    QLabel signupLabel,
           loginLabel,
           passwordLabel,
           passwordConfirmationLabel;
    QLineEdit loginText,
              passwordText,
              passwordConfirmationText;
    QPushButton signUpButton,
                backButton;
    QGridLayout *grid;
private slots:
    void signUpFunction();
    void backFunction();
public:
    SignupMenu(Game *game, QGridLayout *grid);
    ~SignupMenu();
    void display() override;
    void hide() override;
};

#endif  // INCLUDE_SIGNUPMENU_H_
