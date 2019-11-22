#ifndef INCLUDE_POPUPINVENTORYMENU_H_
#define INCLUDE_POPUPINVENTORYMENU_H_
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include "menu.h"

class PopUpInventoryMenu : public Menu {
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
public:
    PopUpInventoryMenu(Game *game);
    ~PopUpInventoryMenu();
    void updateInventoryTables();
    void display() override;
    void hide() override;
};

#endif  // INCLUDE_POPUPINVENTORYMENU_H_
