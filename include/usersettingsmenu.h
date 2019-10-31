#ifndef INCLUDE_USERSETTINGSMENU_H_
#define INCLUDE_USERSETTINGSMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include "menu.h"

class UsersettingsMenu : public Menu {
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
    void display() override;
    void hide() override;
};

#endif  // INCLUDE_USERSETTINGSMENU_H_
