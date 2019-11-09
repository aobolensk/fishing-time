#ifndef INCLUDE_STOREMENU_H_
#define INCLUDE_STOREMENU_H_
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include "menu.h"

class StoreMenu : public Menu {
private:
    Q_OBJECT
private:
    QLabel selectedItemLabel,
           infoLabel;
    QLineEdit quantityText;
    QPushButton buyButton,
                backButton;
    QTableWidget storeTable;
    QTableWidgetItem idHeader,
                     nameHeader,
                     priceHeader;
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
