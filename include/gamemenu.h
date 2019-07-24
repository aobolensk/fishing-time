#ifndef INCLUDE_GAMEMENU_H_
#define INCLUDE_GAMEMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QTableWidget>
#include <QComboBox>

class Game;

class GameMenu : public QObject {
private:
    Q_OBJECT
private:
    Game *game;
    QPushButton clickButton,
                backButton,
                inventoryButton,
                netsButton,
                marketButton,
                storeButton,
                statisticsButton;
    QLabel infoLabel,
           fishLabel;
    QTableWidget table;
    QTableWidgetItem nameHeader,
                     quantityHeader;
    QComboBox locationSelector;
    QGridLayout *grid;
private slots:
    void clickFunction();
    void backFunction();
    void inventoryFunction();
    void marketFunction();
    void storeFunction();
    void netsFunction();
    void statisticsFunction();
private:
    void updateInfo();
public:
    void updateInventoryTable();
public:
    GameMenu(Game *game, QGridLayout *grid);
    ~GameMenu();
    void display();
    void hide();
};

#endif  // INCLUDE_GAMEMENU_H_
