#ifndef INCLUDE_LOGINMENU_H_
#define INCLUDE_LOGINMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>

class Game;

class LoginMenu : public QObject {
private:
    Q_OBJECT
private:
    Game *game;
    QLineEdit loginText,
              passwordText;
    QPushButton loginButton,
                signUpButton,
                demoButton,
                backButton;
    QGridLayout *grid;
private slots:
    void loginFunction();
    void signUpFunction();
    void demoFunction();
    void backFunction();
public:
    LoginMenu(Game *game, QGridLayout *grid);
    ~LoginMenu();
    void display();
    void hide();
};

#endif  // INCLUDE_LOGINMENU_H_
