#ifndef INCLUDE_NETSMENU_H_
#define INCLUDE_NETSMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>

class Game;

class NetsMenu : public QObject {
private:
    Q_OBJECT
private:
    Game *game;
    QPushButton backButton;
    QGridLayout *grid;
private slots:
    void backFunction();
public:
    NetsMenu(Game *game, QGridLayout *grid);
    ~NetsMenu();
    void display();
    void hide();
};

#endif  // INCLUDE_NETSMENU_H_
