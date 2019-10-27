#ifndef INCLUDE_LOGINMENU_H_
#define INCLUDE_LOGINMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QComboBox>
#include "menu.h"

class LoginMenu : public Menu {
private:
    Q_OBJECT
private:
    Game *game;
    QComboBox loginSelector;
    QLineEdit passwordText;
    QPushButton loginButton,
                signUpButton,
                forgotPasswordButton,
                demoButton,
                backButton;
    QGridLayout *grid;
private slots:
    void loginFunction();
    void signUpFunction();
    void forgotPasswordFunction();
    void demoFunction();
    void backFunction();
public:
    LoginMenu(Game *game, QGridLayout *grid);
    ~LoginMenu();
    void display() override;
    void hide() override;
    bool isDisplayed() const;
};

#endif  // INCLUDE_LOGINMENU_H_
