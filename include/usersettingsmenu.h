#ifndef INCLUDE_USERSETTINGSMENU_H_
#define INCLUDE_USERSETTINGSMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>

class Game;

class UsersettingsMenu : public QObject {
private:
    Q_OBJECT
private:
    Game *game;
    QLabel usersettingsLabel,
           oldPasswordLabel,
           newPasswordLabel,
           newPasswordConfirmationLabel,
           changePasswordLabel;
    QLineEdit oldPasswordText,
              newPasswordText,
              newPasswordConfirmationText;
    QPushButton deleteAccountButton,
                changePasswordButton,
                backButton;
    QGridLayout *grid;
private slots:
    void changePasswordFunction();
    void deleteAccountFunction();
    void backFunction();
public:
    UsersettingsMenu(Game *game, QGridLayout *grid);
    ~UsersettingsMenu();
    void display();
    void hide();
};

#endif  // INCLUDE_USERSETTINGSMENU_H_
