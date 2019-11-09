#ifndef INCLUDE_MAINMENU_H_
#define INCLUDE_MAINMENU_H_
#include <QLabel>
#include <QPushButton>
#include "menu.h"

class MainMenu : public Menu {
private:
    Q_OBJECT
private:
    QLabel infoLabel;
    QPushButton consoleButton,
                startButton,
                settingsButton,
                ratingButton,
                aboutButton,
                reportButton,
                exitButton;
    int cnt = 0;
private slots:
    void consoleFunction();
    void startFunction();
    void settingsFunction();
    void ratingFunction();
    void aboutFunction();
    void reportFunction();
    void exitFunction();
public:
    MainMenu(Game *game, QGridLayout *grid);
    ~MainMenu();
    void display() override;
    void hide() override;
};

#endif  // INCLUDE_MAINMENU_H_
