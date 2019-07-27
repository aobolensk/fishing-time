#ifndef INCLUDE_USERSETTINGSMENU_H_
#define INCLUDE_USERSETTINGSMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>

class Game;

class UsersettingsMenu : public QObject {
private:
    Q_OBJECT
private:
    Game *game;
    QLabel usersettingsText;
    QPushButton backButton;
    QGridLayout *grid;
private slots:
    void backFunction();
public:
    UsersettingsMenu(Game *game, QGridLayout *grid);
    ~UsersettingsMenu();
    void display();
    void hide();
};

#endif  // INCLUDE_USERSETTINGSMENU_H_
