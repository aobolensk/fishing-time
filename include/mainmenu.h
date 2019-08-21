#ifndef INCLUDE_MAINMENU_H_
#define INCLUDE_MAINMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QApplication>
#include <QLabel>

class Game;

class MainMenu : public QObject {
private:
    Q_OBJECT
private:
    Game *game;
    QLabel infoLabel;
    QPushButton consoleButton,
                startButton,
                settingsButton,
                ratingButton,
                exitButton;
    QGridLayout *grid;
    int cnt = 0;
private slots:
    void consoleFunction();
    void startFunction();
    void settingsFunction();
    void ratingFunction();
    void exitFunction();
public:
    MainMenu(Game *game, QGridLayout *grid);
    ~MainMenu();
    void display();
    void hide();
};

#endif  // INCLUDE_MAINMENU_H_
