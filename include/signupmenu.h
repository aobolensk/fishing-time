#ifndef INCLUDE_SIGNUPMENU_H_
#define INCLUDE_SIGNUPMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>

class Game;

class SignupMenu : public QObject {
private:
    Q_OBJECT
private:
    Game *game;
    QLabel signupLabel;
    QLineEdit loginText,
              passwordText;
    QPushButton signUpButton,
                backButton;
    QGridLayout *grid;
private slots:
    void signUpFunction();
    void backFunction();
public:
    SignupMenu(Game *game, QGridLayout *grid);
    ~SignupMenu();
    void display();
    void hide();
};

#endif  // INCLUDE_SIGNUPMENU_H_
