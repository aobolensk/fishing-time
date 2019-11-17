#ifndef INCLUDE_INVENTORYMENU_H_
#define INCLUDE_INVENTORYMENU_H_
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include "menu.h"

class InventoryMenu : public Menu {
private:
    Q_OBJECT
private:
    QLabel descriptionLabel;
    QTableWidget fishTable,
                 othersTable;
    QTableWidgetItem fishNameHeader,
                     fishQuantityHeader,
                     othersNameHeader,
                     othersQuantityHeader;
    QPushButton backButton;
private slots:
    void backFunction() override;
private:
    void updateInventoryTables();
public:
    InventoryMenu(Game *game, QGridLayout *grid);
    ~InventoryMenu();
    void display() override;
    void hide() override;
};

#endif  // INCLUDE_INVENTORYMENU_H_
