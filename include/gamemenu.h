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
    bool displayed = false;
    Game *game;
    QPushButton clickButton,
                logOutButton,
                backButton,
                inventoryButton,
                netsButton,
                marketButton,
                storeButton,
                statisticsButton,
                usersettingsButton;
    QLabel infoLabel,
           fishLabel;
    QTableWidget popUpInventoryTable;
    QTableWidgetItem nameHeader,
                     quantityHeader;
    QComboBox locationSelector;
    QGridLayout *grid;
private slots:
    void clickFunction();
    void logOutFunction();
    void backFunction();
    void inventoryFunction();
    void marketFunction();
    void storeFunction();
    void netsFunction();
    void statisticsFunction();
    void usersettingsFunction();
private:
    void updateInfo();
public:
    void updateInventoryTable();
public:
    GameMenu(Game *game, QGridLayout *grid);
    ~GameMenu();
    void display();
    void hide();
    bool isDisplayed() const;
};

#endif  // INCLUDE_GAMEMENU_H_
