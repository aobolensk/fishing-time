#ifndef INCLUDE_MAINMENU_H_
#define INCLUDE_MAINMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QApplication>

class Game;

class MainMenu : public QObject {
private:
    Q_OBJECT
private:
    Game *game;
    QPushButton startButton,
                settingsButton,
                exitButton;
    QGridLayout *grid;
    int cnt = 0;
private slots:
    void startFunction();
    void settingsFunction();
    void exitFunction();
public:
    MainMenu(Game *game, QGridLayout *grid);
    ~MainMenu();
    void display();
    void hide();
};

#endif  // INCLUDE_MAINMENU_H_
