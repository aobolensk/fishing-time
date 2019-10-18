#ifndef INCLUDE_LOCATIONMENU_H_
#define INCLUDE_LOCATIONMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include "menu.h"

class LocationMenu : public Menu {
private:
    Q_OBJECT
private:
    Game *game;
    bool displayed = false;
    QLabel descriptionLabel;
    QPushButton backButton;
    QComboBox locationSelector;
    QMetaObject::Connection locationUpdater;
    QGridLayout *grid;
private slots:
    void backFunction();
public:
    LocationMenu(Game *game, QGridLayout *grid);
    ~LocationMenu();
    void display() override;
    void hide() override;
    bool isDisplayed() const;
};

#endif  // INCLUDE_LOCATIONMENU_H_
