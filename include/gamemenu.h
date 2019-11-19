#ifndef INCLUDE_GAMEMENU_H_
#define INCLUDE_GAMEMENU_H_
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include "menu.h"

class GameMenu : public Menu {
private:
    Q_OBJECT
private:
    QPushButton clickButton,
                profileButton,
                logOutButton,
                backButton,
                inventoryButton,
                netsButton,
                marketButton,
                storeButton,
                statisticsButton,
                usersettingsButton,
                locationButton;
    QLabel infoLabel,
           fishLabel;
    QTableWidget popUpInventoryTable;
    QTableWidgetItem nameHeader,
                     quantityHeader;
protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
public slots:
    void logOutFunction();
    void clickFunction();
private slots:
    void profileFunction();
    void backFunction() override;
    void inventoryFunction();
    void marketFunction();
    void storeFunction();
    void netsFunction();
    void statisticsFunction();
    void usersettingsFunction();
    void locationFunction();
private:
    bool displayedButtons = true;
    void displayButtons();
    void hideButtons();
public:
    void updateInfo();
    void updateInventoryTable();
    QTableWidget &getPopUpInventoryTable();
public:
    GameMenu(Game *game, QGridLayout *grid);
    ~GameMenu();
    void display() override;
    void hide() override;
};

#endif  // INCLUDE_GAMEMENU_H_
