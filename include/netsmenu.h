#ifndef INCLUDE_NETSMENU_H_
#define INCLUDE_NETSMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QTimer>
#include "menu.h"
#include "config.h"

class NetsMenu : public Menu {
private:
    Q_OBJECT
private:
    Game *game;
    QPushButton backButton;
    QLabel netsDescription,
           netSlotLabel[Config::SLOTS_COUNT];
    QComboBox netSlot[Config::SLOTS_COUNT];
    QString nets[Config::SLOTS_COUNT];
    QTimer netsTimer;
    QGridLayout *grid;
private:
    void updateNets();
private slots:
    void netsTimerTick();
private slots:
    void backFunction();
public:
    NetsMenu(Game *game, QGridLayout *grid);
    ~NetsMenu();
    void display() override;
    void hide() override;
    void foldNets();
};

#endif  // INCLUDE_NETSMENU_H_
