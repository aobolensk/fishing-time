#ifndef INCLUDE_STOREMENU_H_
#define INCLUDE_STOREMENU_H_
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "menu.h"
#include "config.h"

class StoreMenu : public Menu {
private:
    Q_OBJECT
private:
    struct Item {
        QString id;
        qint64 price;
        Item() = default;
        Item(const QString &id, qint64 price) :
            id(id),
            price(price) {
        }
        ~Item() = default;
    } item[Config::STORE_MAX_ITEMS_COUNT];
    QLabel itemLabel[Config::STORE_MAX_ITEMS_COUNT],
           infoLabel;
    QLineEdit quantityText[Config::STORE_MAX_ITEMS_COUNT];
    QPushButton buyButton[Config::STORE_MAX_ITEMS_COUNT],
                backButton;
private slots:
    void buyFunction(int index);
    void backFunction() override;
private:
    void addItem(const Item &item, int &index);
    void updateInfo();
    void updateTable();
public:
    StoreMenu(Game *game, QGridLayout *grid);
    ~StoreMenu();
    void display() override;
    void hide() override;
};

#endif  // INCLUDE_STOREMENU_H_
