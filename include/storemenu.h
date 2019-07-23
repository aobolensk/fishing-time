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
    Game *game;
    QLabel selectedItemLabel,
           infoLabel;
    QLineEdit quantityText;
    QPushButton buyButton,
                backButton;
    QTableWidget storeTable;
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
};

#endif  // INCLUDE_STOREMENU_H_
