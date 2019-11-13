#ifndef INCLUDE_MARKETMENU_H_
#define INCLUDE_MARKETMENU_H_
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "menu.h"
#include "config.h"

class MarketMenu : public Menu {
private:
    Q_OBJECT
private:
    QPushButton backButton,
                dialogButton[Config::SELLERS_COUNT];
    QLabel descriptionLabel,
           infoLabel,
           dialogLabel[Config::SELLERS_COUNT];
    QLineEdit quantityText[Config::SELLERS_COUNT];
    QString goodId[Config::SELLERS_COUNT];
    qint64 goodPrice[Config::SELLERS_COUNT];
    QTimer timer;
    QMetaObject::Connection timerUpdater;
    int seed = -1;
private slots:
    void backFunction() override;
    void processDialog(int seller);
    void updateDeals();
private:
    void updateInfo();
public:
    MarketMenu(Game *game, QGridLayout *grid);
    ~MarketMenu();
    void display() override;
    void hide() override;
};

#endif  // INCLUDE_MARKETMENU_H_
