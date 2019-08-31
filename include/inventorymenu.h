#ifndef INCLUDE_INVENTORYMENU_H_
#define INCLUDE_INVENTORYMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QTableWidget>

class Game;

class InventoryMenu : public QObject {
private:
    Q_OBJECT
private:
    bool displayed = false;
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
    void display();
    void hide();
    bool isDisplayed() const;
};

#endif  // INCLUDE_INVENTORYMENU_H_
