#ifndef INCLUDE_STOREMENU_H_
#define INCLUDE_STOREMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QTableWidget>
#include <QLineEdit>
#include <QLabel>

class Game;

class StoreMenu : public QObject {
private:
    Q_OBJECT
private:
    bool displayed = false;
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
    void display();
    void hide();
    bool isDisplayed() const;
};

#endif  // INCLUDE_STOREMENU_H_
