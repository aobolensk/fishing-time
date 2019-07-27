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
    QLabel usersettingsText;
    QPushButton deleteAccountButton,
                backButton;
    QGridLayout *grid;
private slots:
    void deleteAccountFunction();
    void backFunction();
public:
    UsersettingsMenu(Game *game, QGridLayout *grid);
    ~UsersettingsMenu();
    void display();
    void hide();
};

#endif  // INCLUDE_USERSETTINGSMENU_H_
