#ifndef INCLUDE_MARKETMENU_H_
#define INCLUDE_MARKETMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include "menu.h"
#include "config.h"

class MarketMenu : public Menu {
private:
    Q_OBJECT
private:
    Game *game;
    QPushButton backButton,
                dialogButton[Config::SELLERS_COUNT];
    QLabel descriptionLabel,
           infoLabel,
           dialogLabel[Config::SELLERS_COUNT];
    QLineEdit quantityText[Config::SELLERS_COUNT];
    QString goodId[Config::SELLERS_COUNT];
    qint64 goodPrice[Config::SELLERS_COUNT];
    QGridLayout *grid;
private slots:
    void backFunction();
    void processDialog(int seller);
private:
    void updateDeals();
    void updateInfo();
public:
    MarketMenu(Game *game, QGridLayout *grid);
    ~MarketMenu();
    void display() override;
    void hide() override;
};

#endif  // INCLUDE_MARKETMENU_H_
