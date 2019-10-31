#ifndef INCLUDE_INVENTORYMENU_H_
#define INCLUDE_INVENTORYMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QTableWidget>
#include "menu.h"

class InventoryMenu : public Menu {
private:
    Q_OBJECT
private:
    Game *game;
    QLabel descriptionLabel;
    QTableWidget inventoryTable;
    QTableWidgetItem nameHeader,
                     quantityHeader;
    QPushButton backButton;
    QGridLayout *grid;
private slots:
    void backFunction();
private:
    void updateInventoryTable();
public:
    InventoryMenu(Game *game, QGridLayout *grid);
    ~InventoryMenu();
    void display() override;
    void hide() override;
};

#endif  // INCLUDE_INVENTORYMENU_H_
