#ifndef INCLUDE_LOCATIONMENU_H_
#define INCLUDE_LOCATIONMENU_H_
#include <QLabel>
#include <QPushButton>
#include "menu.h"

class LocationMenu : public Menu {
private:
    Q_OBJECT
private:
    QLabel descriptionLabel;
    QPushButton backButton;
    QComboBox locationSelector;
    QMetaObject::Connection locationUpdater;
private slots:
    void backFunction() override;
public:
    LocationMenu(Game *game, QGridLayout *grid);
    ~LocationMenu();
    void display() override;
    void hide() override;
};

#endif  // INCLUDE_LOCATIONMENU_H_
