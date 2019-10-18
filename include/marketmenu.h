#ifndef INCLUDE_MARKETMENU_H_
#define INCLUDE_MARKETMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include "menu.h"

class MarketMenu : public Menu {
private:
    Q_OBJECT
private:
    bool displayed = false;
    static const int SELLERS_COUNT = 3;
    Game *game;
    QPushButton backButton,
                dialogButton[SELLERS_COUNT];
    QLabel descriptionLabel,
           infoLabel,
           dialogLabel[SELLERS_COUNT];
    QLineEdit quantityText[SELLERS_COUNT];
    QString goodId[SELLERS_COUNT];
    qint64 goodPrice[SELLERS_COUNT];
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
    bool isDisplayed() const;
};

#endif  // INCLUDE_MARKETMENU_H_
