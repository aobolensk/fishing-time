#ifndef INCLUDE_STOREMENU_H_
#define INCLUDE_STOREMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QTableWidget>
#include <QLineEdit>
#include <QLabel>
#include "menu.h"

class StoreMenu : public Menu {
private:
    Q_OBJECT
private:
    Game *game;
    QLabel selectedItemLabel,
           infoLabel;
    QLineEdit quantityText;
    QPushButton buyButton,
                backButton;
    QTableWidget storeTable;
    QTableWidgetItem idHeader,
                     nameHeader,
                     priceHeader;
    QGridLayout *grid;
private slots:
    void buyFunction();
    void backFunction();
private:
    void updateInfo();
    void updateTable();
public:
    StoreMenu(Game *game, QGridLayout *grid);
    ~StoreMenu();
    void display() override;
    void hide() override;
};

#endif  // INCLUDE_STOREMENU_H_
